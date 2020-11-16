#ifndef CLIENTCPNET_H
#define CLIENTCPNET_H

#include "clientinterface.h"
#include <libcpnet-dev/src/cpnet-network.h>

class ClientCpnet : public ClientInterface
{
public:
    ClientCpnet(std::string Address, int Port, int bufferSize,
                int socketType=UDP, int Protocol = IP);
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
