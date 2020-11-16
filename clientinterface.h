#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <string>

class ClientInterface
{
public:
    ClientInterface();
    virtual ~ClientInterface();

    virtual bool initClient() = 0;
    virtual void startClient() = 0;
    virtual bool connectToServer() = 0;
    virtual bool writeToServer(std::string word) = 0;
    virtual bool readFromServer(std::string &readFromServer) = 0;
    virtual void closeClient() = 0;

    std::string getServerAddress() const;
    void setServerAddress(const std::string &value);

    uint16_t getServerPort() const;
    void setServerPort(const uint16_t &value);

public:
    enum SOCKET_TYPE {TCP, UDP};
    enum PROTOCOL {IP};

    int getSocketType() const;
    void setSocketType(int value);

    int getProtocol() const;
    void setProtocol(int value);

    uint16_t getBufferSize() const;
    void setBufferSize(const uint16_t &value);

protected:
    std::string serverAddress;
    uint16_t bufferSize;
    int serverPort;
    int SocketType;
    int Protocol;
};

#endif // CLIENTINTERFACE_H
