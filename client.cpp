#include "client.h"
#include <algorithm>
#include "md5.h"
#include <fstream>
#include <iostream>
#include "messageprotocol.h"
#include <socketexception.h>

using namespace std;

Client::Client(string serverAddress, int serverPort, int bufferSize, int SocketType, int protocol)

{
    clientInfrastructure = new ClientCpnet(serverAddress, serverPort, bufferSize,
                             SocketType, protocol);
    console = new Console(cout, cin);

}

Client::~Client()
{
    delete clientInfrastructure;
    delete console;
}

void Client::initiate()
{
    if(!clientInfrastructure->initClient())
        throw SocketException("Failed initializing client", "initialization");


}

bool Client::sendMessage(string message)
{
    MessageProtocol messageProtocol(message);
    messageProtocol.setCommand("message");

    return sendMessage(messageProtocol);

}

bool Client::sendMessage(MessageProtocol &message)
{
    return clientInfrastructure->
            writeToServer(message.serializeMessage());
}

MessageProtocol Client::readMessage()
{
    MessageProtocol messageProtocol;
    string readedMessage;
    bool result =  clientInfrastructure->readFromServer(readedMessage);
    if (!result )
    {
        throw SocketException("Failed to read message", "Read");
    }

    messageProtocol.deSerializeMessage(readedMessage);
    return messageProtocol;
}


string Client::sendCommand(string command, string data[])
{
    string response;

    //  if-else block will check "command" against a set of
    //  predefined commands. It provides the parameters and call the
    //  appropriate helper function.

    // TO-DO : improve the block and replace it with map collection.
    try {
        if (command.find("login") != string::npos)
        {
            response =login(data);
        }
        else if (command.find("getfile") != string::npos)
        {
            string fileName = data[0];
            MessageProtocol getFileMessage(fileName);
            getFileMessage.setCommand("getfile");
            this->sendMessage(getFileMessage);
            response = this->readMessage().getData()[0];
            if (response.find("sendingFile") != string::npos)
            {
                try {
                    response = recieveFile(fileName);
                } catch (const SocketException &e) {
                    console->writeLine("Action:" + e.getAction() +
                                      "Failed with the message:" +
                                      e.what());
                    return "Error reciveving file";

                }catch(const runtime_error &e)
                {
                    console->writeLine(e.what());
                    return "Runtime error!";
                }
            }

        }else if (command.find("logout") != string::npos)
        {

            response = logout();
        }
        else if (command.find("quit") != string::npos)
        {
            MessageProtocol quitMessage("Client is shutting down.");
            quitMessage.setCommand("quit");
            this->sendMessage(quitMessage);
        } else {
            console->writeLine("Bad Input command!");
        }


    } catch (const SocketException &e) {
        console->writeLine("Action:" + e.getAction() +
                          "Failed with the message:" +
                          e.what());
    }

    console->write("Clinet>>"+response);
    return response;
}

string Client::recieveFile(string fileName)
{
    uint16_t bufferSize = clientInfrastructure->getBufferSize();
    string buffer;

    if (!this->clientInfrastructure->readFromServer(buffer))
        throw SocketException("Failed to recieve file", "read");

    if (buffer.find("fileNotFound") != string::npos)
    {
        return "Client>>Bad file request";
    }

    console->writeLine("Client>>Start recieving file...");

    //  Get the file size so that can calculate loop count and remained bytes.
    int fileSize = stoi(buffer);
    ofstream outStream("rec" + fileName);

    if (!outStream.good())
    {
        throw runtime_error("Failed to save recieved file");

    }

    int loopCount = fileSize / bufferSize;
    int remaindedBytes= fileSize % bufferSize;
    for (int loop = 0; loop < loopCount; loop++)
    {
        if (!clientInfrastructure->readFromServer(buffer))
        {
            throw SocketException("Failed to recieve file", "read");

        }
        console->writeLine("Client>>"+md5(buffer));
        outStream.write(buffer.c_str(), bufferSize);

    }

    if (!clientInfrastructure->readFromServer(buffer))
    {
        throw SocketException("Failed to recieve file", "read");
    }

    outStream.write(buffer.c_str(), remaindedBytes);

    outStream.close();

    return "finished recieving file";

}


bool Client::connect()
{
    return clientInfrastructure->connectToServer();
}

string Client::login(string userInfo[])
{
    MessageProtocol user(2, userInfo);
    user.setCommand("login");
    this->sendMessage(user);

    try {
        return (this->readMessage().getData()[0]);
    } catch (SocketException &e) {
        e.setAction("login");
        throw;
    }

}

string Client::logout()
{

    MessageProtocol logoutMessage;
    logoutMessage.setCommand("logout");
    this->sendMessage(logoutMessage);

    try {
        return this->readMessage().getData()[0];

    } catch (SocketException &e) {
        e.setAction("logout");
        throw;
    }

}


void Client::setOutStream(ostream &outStream)
{
    this->console->setOutputStream(outStream);
}

void Client::setInStream(istream &inStream)
{
    this->console->setInputStream(inStream);
}

void Client::close()
{
    clientInfrastructure->closeClient();
}






