#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "serverinterface.h"
#include "servercpnet.h"
#include "user.h"
#include "console.h"
#include <iostream>
#include "messageprotocol.h"


/**
 * @brief The Server class manages the actions of a Dedicated server.
 * @details This Class manages starting, stopping, logging in, logging out and
 *  Files of  of an instance server.
 */
class Server
{
public:
    Server();
    Server(const std::string address, int port,
           int sockType, int protocol, int bufferSize);
    ~Server();

    /**
     * @brief Waits for incoming message from clients, and handles them.
     *
     */
    void getCommand();

    /**
     * @brief this method takes the appropriate action based on the incoming
     *  message.
     * @param newMessage The incoming message to be interpreted.
     * @throws SocketException, runtime_error
     * @details This method will call appropriate helper method according to
     *  the recieved command. it attempts to handle different scenarios which
     *  may occur.
     */
    void commandInterpreter(MessageProtocol &newMessage );


    /**
     * @brief helper function to handle login request.
     * @param recUsername recieved Usename.
     * @param recPassword recieved Passwrord.
     */
    void login(string recUsername, string recPassword);

    /**
     * @brief helper function to handle logout request.
     */
    void logout();


    /**
     * @brief Manages requests for files.
     * @param fileName Requested file name.
     * @throw SocketException
     * @details It handles the file requets from client. It may send the file in
     *  multiparts based on the buffer size or inform the client that the
     *  requested file does not exist or corrupted.
     */
    void sendFileToClient(std::string &fileName);

    /**
     * @brief Send a plaint text Message with command "message".
     * @param message Plain text to send.
     * @return true if the message sent successfully.
     */
    bool sendMessage(std::string message);

    /**
     * @brief Send a message with optional data and command.
     * @param message message protocol to send.
     * @return true if the message sent successfully.
     */
    bool sendMessage(MessageProtocol message);

    /**
     * @brief Initiate the server.
     * @throws SocketException
     */
    void initiate();
    void listen();
    bool accpet();

    /**
     * @brief Read message from the network and extracts the command and data.
     * @return A message protocol with appropriate command and data.
     * @throws SocketException
     */
    MessageProtocol readMessage();

    /**
     * @brief helper function for Handling login requests.
     * @param newUser User to be logged in.
     * @return true if the login is successful.
     */
    bool checkLogin(User &newUser);

    /**
     * @brief Start the server in an infinite loop to handle client requests.
     */
    void startServer();
    void close();

    /**
     * @brief Sets and stream to write the log and output of the server to it.
     * @param outStream Output stream.
     */
    void setOutStream( ostream &outStream);

private:
    /**
     * @brief Create admin users.json file.
     * @throws runtime_error
     */
    void createUserFile();


private:
    bool isLogin = false;
    ServerInterface* serverInfrastructure;
    Console* console;

    bool isStop = false;


};

#endif // SERVER_H
