#ifndef CLIENT_H
#define CLIENT_H


#include "clientinterface.h"
#include "clientcpnet.h"
#include "syncoutput.h"
#include "syncinput.h"
#include <vector>
#include <string>
#include <iostream>
#include "messageprotocol.h"

class Client
{
public:
    Client(std::string serverAddress, int serverPort, int bufferSize,
           int SocketType, int protocol);
    ~Client();

    bool initiate();
    bool sendMessage(std::string message);
    bool sendMessage(MessageProtocol message);
    MessageProtocol readMessage();

    std::string sendCommand(std::string command, std::string data[]= nullptr);
    std::string recieveFile(std::string fileName);

    bool connect();

    std::string login(std::string userInfo[]);
    std::string logout();

    void setOutStream(std::ostream &outStream);
    void setInStream(std::istream &inStream);
    void close();


private:

    ClientInterface * clientInfrastructure;
    std::vector<std::string> commandList = {"login", "getfile", "logout"};
    SyncOutput *output;
    SyncInput *input;

};

#endif // CLIENT_H
