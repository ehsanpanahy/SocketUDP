#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <string>

/**
 * @brief An Interface(Abstract class) for Client Infrastructure.
 * @details This interface decouples the implementation of client infrastrucure
 *  from the underlying library(Unix, boost, win32,...). That way the user of the
 *  client class does not need to be concerned about the platform which
 *   app is running in.
 */
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

    int getServerPort() const;
    void setServerPort(const int &value);

public:

    int getSocketType() const;
    void setSocketType(int value);

    int getProtocol() const;
    void setProtocol(int value);

    uint16_t getBufferSize() const;
    void setBufferSize(const uint16_t &value);

protected:
    std::string serverAddress;
    int bufferSize;
    int serverPort;
    int SocketType;
    int Protocol;
};

#endif // CLIENTINTERFACE_H
