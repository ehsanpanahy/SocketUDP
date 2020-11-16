#ifndef COMMANDLINEINTERFACE_H
#define COMMANDLINEINTERFACE_H

#include "client.h"
#include <iostream>
#include <string>

class CommandLineInterface
{
public:
    CommandLineInterface(Client &client);

    void startClient();


private:
    std::string commandInterpreter(std::string &command);
    void getPassword(std::string &password);

private:
    Client* client;


};

#endif // COMMANDLINEINTERFACE_H
