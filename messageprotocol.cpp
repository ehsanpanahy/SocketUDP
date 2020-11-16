#include "messageprotocol.h"

using namespace std;

MessageProtocol::MessageProtocol()
{

}

MessageProtocol::MessageProtocol(string message)
{
    data.push_back(message);
}

MessageProtocol::MessageProtocol(int argc, string argv[])
{
    for (int i = 0; i < argc; i++)
    {
        data.push_back(argv[i]);
    }
}

MessageProtocol::~MessageProtocol()
{

}


std::string MessageProtocol::serializeMessage()
{
    string serialMessage;
    for (string s : data )
    {
        serialMessage.append(delimiter);
        serialMessage.append(s);

    }

    serialMessage = command + serialMessage;
    this->size = serialMessage.length();
    return to_string(size) + delimiter + serialMessage;
}

void MessageProtocol::deSerializeMessage(string message)
{
    string messageSize =  message.substr(0, message.find(delimiter));
    ssize_t ss = stoi(messageSize);

    string recMessage = message.substr(message.find("-")+1, ss);
    this->size = recMessage.length();

    data.clear();

    int pos = 0;
    while(pos != std::string::npos)
    {
        pos = recMessage.find(delimiter);
        string m = recMessage.substr(0, pos);
        data.push_back(m);
        recMessage = recMessage.erase(0, pos + delimiter.length());

    }

    command = data[0];
    data.erase(data.begin());
}


std::string MessageProtocol::getCommand() const
{
    return command;
}

std::vector<std::string> MessageProtocol::getData() const
{
    return data;
}

void MessageProtocol::addData(const string data)
{
    this->data.push_back(data);
}

std::string MessageProtocol::getDelimiter() const
{
    return delimiter;
}

void MessageProtocol::setDelimiter(const std::string &value)
{
    delimiter = value;
}

void MessageProtocol::setCommand(const std::string &value)
{
    command = value;
}




