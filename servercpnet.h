#ifndef SERVERCPNET_H
#define SERVERCPNET_H
#include "serverinterface.h"
#include <libcpnet-dev/src/cpnet-network.h>

#include <string>
class ServerCpnet : public ServerInterface
{
public:
    ServerCpnet();
    ServerCpnet(std::string Address, int Port, int bufferSize,
                int socketType=TCP, int Protocol = IP );
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
