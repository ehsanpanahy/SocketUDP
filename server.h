#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "serverinterface.h"
#include "servercpnet.h"
#include "user.h"
#include "syncoutput.h"
#include <iostream>
#include "messageprotocol.h"



class Server
{
public:
    Server();
    Server(const std::string address, int port,
           int sockType, int protocol, int bufferSize);
    ~Server();

    void getCommand();
    void commandProcessor(MessageProtocol &newMessage );
    void login(string recUsername, string recPassword);
    void logout();
    void sendFileToClient(std::string &fileName);
    bool sendMessage(std::string message);
    bool sendMessage(MessageProtocol message);
    void initiate();
    void listen();
    bool accpet();
    MessageProtocol readMessage();
    bool checkLogin(User &newUser);
    void startServer();
    void close();

    void setOutStream( ostream &outStream);

private:
    void createUserFile();


private:
    bool isLogin = false;
    ServerInterface* serverInfrastructure;
    SyncOutput* output;

    bool isStop = false;


};

#endif // SERVER_H
