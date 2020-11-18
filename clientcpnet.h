#ifndef CLIENTCPNET_H
#define CLIENTCPNET_H

#include "clientinterface.h"
#include <libcpnet-dev/src/cpnet-network.h>
#include "commons.h"

/**
 * @brief An implementation for client infrastructure based on Cpnet library.
 * @param Address Client address
 * @param Port Client port
 * @param bufferSize the buffer size to share data between client and server.
 * @param socketType UDP or SREAM socket type.
 * @param Protocol IP Protocol.
 */

class ClientCpnet : public ClientInterface
{
public:
    ClientCpnet(std::string Address, int Port, int bufferSize,
                int socketType=Commons::UDP_SOCKET,
                int Protocol = Commons::IP_RPOTOCOL);
    ~ClientCpnet();

    // ClientInterface interface
public:
    bool initClient();
    void startClient();
    bool connectToServer();
    bool writeToServer(std::string word);
    bool readFromServer(std::string &readFromServer);
    void closeClient();


    int getBufferSize() const;
    void setBufferSize(int value);

private:
    socket_t socketFd;

};

#endif // CLIENTCPNET_H
