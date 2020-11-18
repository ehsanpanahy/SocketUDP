#ifndef SERVERCPNET_H
#define SERVERCPNET_H
#include "serverinterface.h"
#include <libcpnet-dev/src/cpnet-network.h>

#include "commons.h"
#include <string>

/**
 * @brief An implementation for server infrastructure based on Cpnet library.
 * @param Address Client address
 * @param Port server port
 * @param bufferSize the buffer size to share data between client and server.
 * @param socketType UDP or STREAM socket type.
 * @param Protocol IP Protocol.
 */
class ServerCpnet : public ServerInterface
{
public:
    ServerCpnet();
    ServerCpnet(std::string Address, int Port, int bufferSize,
                int socketType=Commons::UDP_SOCKET,
                int Protocol = Commons::IP_RPOTOCOL );
    ~ServerCpnet();

    // ServerInterface interface
public:
    bool initServer();
    bool bindServer();
    void listenToClients(int backLog);
    bool acceptClient(std::string address, int port);
    bool writeToClient(std::string word, std::string peerAddrees, int peerPort);
    bool readFromClient(std::string &read);
    bool closeServer();


private:
    socket_t socketFd;
    socket_t clientFd;

};

#endif // SERVERCPNET_H
