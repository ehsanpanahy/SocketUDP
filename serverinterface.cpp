#include "serverinterface.h"


ServerInterface::ServerInterface()
{

}

ServerInterface::~ServerInterface()
{

}

std::string ServerInterface::getServerAddress() const
{
    return serverAddress;
}

void ServerInterface::setServerAddress(const std::string &value)
{
    serverAddress = value;
}

int ServerInterface::getServerPort() const
{
    return serverPort;
}

void ServerInterface::setServerPort(int value)
{
    serverPort = value;
}

int ServerInterface::getSocketType() const
{
    return SocketType;
}

void ServerInterface::setSocketType(int value)
{
    SocketType = value;
}

int ServerInterface::getProtocol() const
{
    return Protocol;
}

void ServerInterface::setProtocol(int value)
{
    Protocol = value;
}

uint16_t ServerInterface::getBufferSize() const
{
    return bufferSize;
}

void ServerInterface::setBufferSize(const uint16_t &value)
{
    bufferSize = value;
}

std::string ServerInterface::getClientAddress() const
{
    return clientAddress;
}

int ServerInterface::getClientPort() const
{
    return clientPort;
}
