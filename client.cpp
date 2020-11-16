#include "client.h"
#include <algorithm>
#include "md5.h"
#include <fstream>
#include <iostream>
#include "messageprotocol.h"

using namespace std;

Client::Client(string serverAddress, int serverPort, int bufferSize, int SocketType, int protocol)

{
    clientInfrastructure = new ClientCpnet(serverAddress, serverPort, bufferSize,
                             SocketType, protocol);
    output = new SyncOutput(cout);
    input = new SyncInput(cin);
}

Client::~Client()
{
    delete clientInfrastructure;
    delete output;
    delete input;
}

bool Client::initiate()
{

    return clientInfrastructure->initClient();
}

bool Client::sendMessage(string message)
{
    MessageProtocol messageProtocol(message);
    messageProtocol.setCommand("message");

    return sendMessage(messageProtocol);

}

bool Client::sendMessage(MessageProtocol message)
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
        messageProtocol.addData("Failed to read message");
        return messageProtocol ;
    }

    messageProtocol.deSerializeMessage(readedMessage);
    return messageProtocol;
}


string Client::sendCommand(string command, string data[])
{
    string response;

    if (command.find("login") != string::npos)
    {

        response =login(data);

    }else if (command.find("getfile") != string::npos)
    {
        string fileName = data[0];
        MessageProtocol getFileMessage(fileName);
        getFileMessage.setCommand("getfile");
        this->sendMessage(getFileMessage);
        response = this->readMessage().getData()[0];
        if (response.find("sendingFile") != string::npos)
        {
            response = recieveFile(fileName);
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
        output->writeLine("Bad Input command!");
    }

    output->write("Clinet>>"+response);
    return response;
}

string Client::recieveFile(string fileName)
{
    uint16_t bufferSize = clientInfrastructure->getBufferSize();
    string buffer;

    this->clientInfrastructure->readFromServer(buffer);
    if (buffer.find("fileNotFound") != string::npos)
    {
        return "Client>>Bad file request";
    }

    output->writeLine("Client>>Start recieving file...");

    int fileSize = stoi(buffer);
    ofstream outStream("rec" + fileName);

    if (!outStream.good())
    {
        return "Client>>failed to write file!";

    }

    int loopCount = fileSize / bufferSize;
    int remaindedBytes= fileSize % bufferSize;
    for (int loop = 0; loop < loopCount; loop++)
    {
        if (!clientInfrastructure->readFromServer(buffer))
        {
            return "Client>>Failed in recieving file";

        }
        output->writeLine("Client>>"+md5(buffer));
        outStream.write(buffer.c_str(), bufferSize);

    }
    if (!clientInfrastructure->readFromServer(buffer))
    {
        return "Client>>Failed in recieving file";

    }

    outStream.write(buffer.c_str(), remaindedBytes);

    outStream.close();
    return "Client>>finished recieving file";

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
    return (this->readMessage().getData()[0]);
}

string Client::logout()
{

    MessageProtocol logoutMessage;
    logoutMessage.setCommand("logout");
    this->sendMessage(logoutMessage);

    return this->readMessage().getData()[0];
}


void Client::setOutStream(ostream &outStream)
{
    this->output->setStream(outStream);
}

void Client::setInStream(istream &inStream)
{
    this->input->setStream(inStream);
}

void Client::close()
{
    clientInfrastructure->closeClient();
}






