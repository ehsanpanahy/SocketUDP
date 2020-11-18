#include "servercpnet.h"
#include <cstring>
#include "commons.h"

using namespace std;

ServerCpnet::ServerCpnet()
{

}

ServerCpnet::ServerCpnet(std::string Address, int Port,
                         int bufferSize, int socketType, int Protocol)
{
    setServerAddress(Address);
    setServerPort(Port);
    if (socketType == Commons::UDP_SOCKET)
        setSocketType(SOCK_DGRAM);
    else
        setSocketType(SOCK_STREAM);

    setProtocol(0);

    this->bufferSize = bufferSize;
}

ServerCpnet::~ServerCpnet()
{

}



bool ServerCpnet::initServer()
{

    cpnet_init();
    socketFd = cpnet_socket(SocketType);
    if (socketFd == -1)
        return false;

    return true;
}

bool ServerCpnet::bindServer()
{
    char address[serverAddress.length()];
    strcpy(address, serverAddress.c_str());

    uint16_t port = (uint16_t) serverPort;
    //uint16_t port = 9734;
    int bindResult = cpnet_bind(socketFd, address, &port );

    if (bindResult == 0)
        return true;

    return false;
}

void ServerCpnet::listenToClients(int backLog)
{
    if (SocketType != SOCK_STREAM) return;

    cpnet_listen(socketFd, backLog);
}

bool ServerCpnet::acceptClient(std::string address, int port)
{
    if (SocketType != SOCK_STREAM) return false;

    //clientFd = cpnet_accept(socketFd, address.c_str(), port);
    return false;
}

bool ServerCpnet::writeToClient(std::string word,
                                std::string peerAddrees, int peerPort)
{
    char address[peerAddrees.length()];
    strcpy(address, peerAddrees.c_str());
    uint16_t port = peerPort;


    char buffer[bufferSize];
    ssize_t n_bytes;

    //  We try to send minimum number of bytes. thus if the message size is
    // smaller than buffer size, we just copy and sends as equal as
    // message length.
    if (word.length() < bufferSize)
    {
       strncpy(buffer, word.c_str(), word.length());
       n_bytes = cpnet_write_packet(socketFd, buffer, word.length(),
                                                address, port);
    }
    else {
        strncpy(buffer, word.c_str(), bufferSize);
        n_bytes = cpnet_write_packet(socketFd, buffer, bufferSize,
                                                 address, port);
    }

    if (n_bytes == -1)
        return false;

    return true;
}




bool ServerCpnet::readFromClient(std::string &read)
{
    char peerAddress[46];
    uint16_t peerPort = 0;
    char buffer[bufferSize];
    ssize_t n_bytes = cpnet_read_packet(socketFd, buffer,
                                        bufferSize,
                                        peerAddress, &peerPort);
    if (n_bytes == -1 )
        return false;

    read.assign(buffer);

    clientAddress.assign(peerAddress);
    clientPort = peerPort;
    return true;
}


bool ServerCpnet::closeServer()
{
    cpnet_clean();
    cpnet_close(socketFd);
    return true;
}



