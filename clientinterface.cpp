#include "clientinterface.h"

ClientInterface::ClientInterface()
{

}

ClientInterface::~ClientInterface()
{

}

std::string ClientInterface::getServerAddress() const
{
    return serverAddress;
}

void ClientInterface::setServerAddress(const std::string &value)
{
    serverAddress = value;
}


int ClientInterface::getServerPort() const
{
    return serverPort;
}

void ClientInterface::setServerPort(const int &value)
{
    serverPort = value;
}

int ClientInterface::getSocketType() const
{
    return SocketType;
}

void ClientInterface::setSocketType(int value)
{
    SocketType = value;
}

int ClientInterface::getProtocol() const
{
    return Protocol;
}

void ClientInterface::setProtocol(int value)
{
    Protocol = value;
}

uint16_t ClientInterface::getBufferSize() const
{
    return bufferSize;
}

void ClientInterface::setBufferSize(const uint16_t &value)
{
    bufferSize = value;
}
