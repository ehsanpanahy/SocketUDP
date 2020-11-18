#include "clientcpnet.h"
#include <cstring>
#include <iostream>
#include "commons.h"


ClientCpnet::ClientCpnet(std::string Address, int Port, int bufferSize, int socketType, int Protocol)

{
    setServerAddress(Address);
    setServerPort(Port);

    if (socketType == Commons::UDP_SOCKET)
        setSocketType(SOCK_DGRAM);
    else
        setSocketType(SOCK_STREAM);

    setProtocol(Protocol);

    this->bufferSize = bufferSize;

}

ClientCpnet::~ClientCpnet()
{

}

bool ClientCpnet::initClient()
{
    cpnet_init();
    socketFd = cpnet_socket(SocketType);
    if (socketFd == -1)
        return false;

    return true;
}

void ClientCpnet::startClient()
{


}

bool ClientCpnet::connectToServer()
{
    if (SocketType == SOCK_DGRAM) return false;

    int connectResult = cpnet_connect(socketFd, serverAddress.c_str(), serverPort);
    if ( connectResult != 0)
    {
        return false;
    }

    return true;

}

bool ClientCpnet::writeToServer(std::string word)
{
    char buffer[bufferSize];
    char address[serverAddress.length()];
    strcpy(address, serverAddress.c_str());
    uint16_t port = serverPort;

    ssize_t writeResult;

    //  We try to send minimum number of bytes. thus if the message size is
    // smaller than buffer size, we just copy and sends as equal as
    // message length.
    if (word.length() < bufferSize)
    {
        strncpy(buffer, word.c_str(), word.length());
        writeResult = cpnet_write_packet(socketFd, buffer, word.length(),
                                address, port);
    }else {
        strncpy(buffer, word.c_str(), bufferSize);
         writeResult = cpnet_write_packet(socketFd, buffer, bufferSize,
                                address, port);
    }


    if (writeResult < 0)
        return false;

    return true;
}

bool ClientCpnet::readFromServer(std::string &read)
{

    char buffer[bufferSize];
    ssize_t recResult = cpnet_read_packet(socketFd, buffer, bufferSize,
                                      NULL, NULL);

    if (recResult < 0)
        return false;

    read.assign(buffer);
    return true;
}

void ClientCpnet::closeClient()
{
    cpnet_clean();
    cpnet_close(socketFd);
}

int ClientCpnet::getBufferSize() const
{
    return bufferSize;
}

void ClientCpnet::setBufferSize(int value)
{
    bufferSize = value;
}











