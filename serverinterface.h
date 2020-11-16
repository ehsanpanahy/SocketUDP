#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H

#include <string>

class ServerInterface
{
public:
    ServerInterface();
    virtual ~ServerInterface();

    virtual bool initServer() = 0;
    virtual bool bindServer() = 0;
    virtual void listenToClients(int backLog) = 0;
    virtual bool acceptClient(std::string address, int port) = 0;
    virtual bool writeToClient(std::string word,
                               std::string peerAddrees,
                               int peerPort) = 0;
    virtual bool readFromClient(std::string &read) = 0;
    virtual bool closeServer() = 0;


    std::string getServerAddress() const;
    void setServerAddress(const std::string &value);

    int getServerPort() const;
    void setServerPort(int value);

    int getSocketType() const;
    void setSocketType(int value);

    int getProtocol() const;
    void setProtocol(int value);


    enum SOCKET_TYPE {TCP, UDP};
    enum PROTOCOL {IP};

    uint16_t getBufferSize() const;
    void setBufferSize(const uint16_t &value);

    std::string getClientAddress() const;

    int getClientPort() const;

protected:
    std::string serverAddress;
    int serverPort;
    int SocketType;
    int Protocol;
    uint16_t bufferSize;

    std::string clientAddress;
    int clientPort;

};

#endif // SERVERINTERFACE_H
