#ifndef COMMANDLINEINTERFACE_H
#define COMMANDLINEINTERFACE_H

#include "client.h"
#include <iostream>
#include <string>

/**
 * @brief A simple command line interface for the application.
 * @details It provides a simple teriminal-based user interface
 *  for application.
 */
class CommandLineInterface
{
public:
    CommandLineInterface(Client &client);

    /**
     * @brief Start client in an infinite loop and waits for commands.
     */
    void startClient();


private:
    /**
     * @brief It handles requests from standard input.
     * @param command
     * @return
     */
    std::string commandInterpreter(std::string &command);

    /**
     * @brief This method echos characters of terminal for entering password.
     * @param password container for entered password.
     * @details This method will alter the settings of terimnal to echos the
     *  input characters. At last it reset changes to defualt.
     */
    void getPassword(std::string &password);

private:
    Client* client;


};

#endif // COMMANDLINEINTERFACE_H
