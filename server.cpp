#include "server.h"
#include "user.h"
#include "md5.h"
#include "messageprotocol.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "socketexception.h"

#include <thread>

using namespace std;

Server::Server()
{

}

Server::Server(const string address, int port,
               int sockType, int protocol, int bufferSize)

{
    serverInfrastructure = new ServerCpnet(address, port, sockType, protocol, bufferSize );
    console = new Console(cout, cin);

    try {
        createUserFile();

    } catch (const runtime_error &e) {
        console->write("Server>>");
        console->writeLine(e.what());
        console->writeLine("Restart the Server");
    }


}

Server::~Server()
{
    delete serverInfrastructure;
    delete console;
}


void Server::initiate()
{
    if (!serverInfrastructure->initServer())
        throw SocketException("Failed to initialize server", "initilization");

    if (!serverInfrastructure->bindServer())
        throw SocketException("Failed to bind server", "bind");
}

void Server::startServer()
{
    while(1)
    {
        console->writeLine("Server>>Waiting for client request:");
        getCommand();
        if (isStop)
        {
            console->writeLine("Server>>Shutting down...");
            break;
        }
    }
    this->close();

}

void Server::close()
{
    serverInfrastructure->closeServer();
}

MessageProtocol Server::readMessage()
{
   MessageProtocol messageProtocol;
   string readedMessage;
   int readResult = serverInfrastructure->readFromClient(readedMessage);

   if (!readResult)
       throw SocketException("Failed to read message", "Read");

   messageProtocol.deSerializeMessage(readedMessage);
   return messageProtocol;

}

bool Server::sendMessage(string message)
{
    MessageProtocol messageProtocol(message);
    messageProtocol.setCommand("message");

    return sendMessage(messageProtocol);
}

bool Server::sendMessage(MessageProtocol message)
{
    int result =  serverInfrastructure->writeToClient(
                            message.serializeMessage(),
                          serverInfrastructure->getClientAddress(),
                          serverInfrastructure->getClientPort());
    return result;
}


void Server::getCommand()
{
    MessageProtocol recievedMessage;

    try {
        recievedMessage= this->readMessage();
    } catch (SocketException e) {
        console->writeLine("Action:"+e.getAction() + "failed"
                          "with the message:"+ e.what());
        return;
    }

    console->write("Server>>Recieved Command: ");
    console->writeLine(recievedMessage.getCommand());

    commandInterpreter(recievedMessage);
}

void Server::commandInterpreter(MessageProtocol &newMessage)
{
    // Extract command and data from message.
    string newCommand = newMessage.getCommand();
    auto newData = newMessage.getData();

    if(newCommand.find("login") != string::npos){
        login(newData[0], newData[1]);

    }else if (newCommand.find("logout") != string::npos) {
        logout();

    }else if(newCommand.find("getfile") != string::npos)
    {
        if (!this->isLogin) {
            console->writeLine("Server>>First login and then request for the file.");
            this->sendMessage("First login and then request for the file.");
            return;
        }

        string fileName = newData[0];
        console->write("Server>>Requested fileName:" );
        console->writeLine(fileName);
        this->sendMessage("sendingFile");
        try {
            sendFileToClient(fileName);

        } catch (const SocketException &e) {
            console->writeLine("Server>>Action:" + e.getAction() + "Failed"
                                "with the message" +
                                e.what());
        }

    }
    else if (newCommand.find("quit") != string::npos)
    {
        isStop = true;
        return;
    }else
    {
        this->sendMessage("Bad input Command! ");

    }

}

void Server::login(string recUsername, string recPassword)
{

    if (this->isLogin)
    {
        console->writeLine("Server>>You are already logged in!");
        this->sendMessage("You are already logged in!");
        return ;
    }

    User newUser;
    newUser.setUserName(recUsername);
    newUser.setHashedPassword(recPassword);

    try {
        if (!checkLogin(newUser))
        {
            console->writeLine("Server>>Login failed!");
            this->sendMessage("Login failed!");
            return;
        }

    } catch (const runtime_error &e) {
        console->write("Server>>");
        console->writeLine(e.what());
        this->sendMessage("Server has encountered an internal error.");
        return ;

    }


    this->isLogin = true;
    console->writeLine("Server>>Login successfully!");
    this->sendMessage("Login successfully!");
}

void Server::logout()
{
    if (!isLogin){
        console->writeLine("You are not logged in!");
        this->sendMessage("You are not logged in!");
        return;
    }

    this->isLogin = false;
    console->writeLine("Server>>Logout successfully!");
    this->sendMessage("Lgout out successfully");
}

void Server::sendFileToClient(string &fileName)
{

    uint16_t bufferSize = serverInfrastructure->getBufferSize();
    char buffer[bufferSize];

    ifstream inputStream;
    inputStream.open(fileName, ifstream::in);

    // Inform the client that the requested file does not exist.
    if (!inputStream)
    {
        console->writeLine("Server>>Bad file request.");
        this->sendMessage("fileNotFound");
        return;
    }

    //  Calculate the file size and send it to the client.
    inputStream.seekg(0, inputStream.end);
    int fileSize = inputStream.tellg();
    inputStream.seekg(0, inputStream.beg);

    if (!this->serverInfrastructure->writeToClient(to_string(fileSize),
                                                        serverInfrastructure->getClientAddress(),
                                                        serverInfrastructure->getClientPort()))
    {
        throw SocketException("Failed to send file to client", "SendFile.");
    }
    console->writeLine("Server>>Start sending file...");

    // Calculate the loop count based on the file size and buffer size. first
    // read and send chunks of bytes to the end of loop count.
    int loopCount = fileSize / bufferSize;
    int remaindedBytes = fileSize % bufferSize;
    for (int loop = 0; loop < loopCount; loop++)
    {
        inputStream.read(buffer, bufferSize);

        console->writeLine("Server>>"+md5(buffer));
        if (!serverInfrastructure->writeToClient(buffer,
                                                 serverInfrastructure->getClientAddress(),
                                                 serverInfrastructure->getClientPort()))
        {
            throw SocketException("Failed to send file to client", "SendFile.");
        }
    }

    // Then read the remainded bytes and send them.
    inputStream.read(buffer, remaindedBytes);
    if (!serverInfrastructure->writeToClient(buffer,
                                             serverInfrastructure->getClientAddress(),
                                             serverInfrastructure->getClientPort()))
    {
        throw SocketException("Failed to send file to client", "SendFile.");

    }

    inputStream.close();

}


bool Server::checkLogin(User &newUser)
{
    ifstream userStream;
    userStream.open("users.json", ifstream::in);

    if (!userStream)
    {
        throw runtime_error("Could not open users.json .");
    }

    User adminUser;
    adminUser.deSerializedUser(userStream);
    userStream.close();

    if (!adminUser.equals(newUser))
        return false;

    return true;

}



void Server::createUserFile()
{
    ofstream userStream("users.json");

    if (!userStream.good())
    {
        throw runtime_error("Error creating users.json");
    }

    User adminUser("admin", "admin");
    adminUser.serializeUser(userStream);

    userStream.close();

}

void Server::listen()
{
    serverInfrastructure->listenToClients(5);
}

bool Server::accpet()
{
    return serverInfrastructure->acceptClient("127.0.0.1", 9734);
}


void Server::setOutStream(ostream &outStream)
{
    console->setOutputStream(outStream);
}





