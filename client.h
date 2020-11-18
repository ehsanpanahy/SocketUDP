#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>

#include "clientinterface.h"
#include "clientcpnet.h"
#include "console.h"
#include "messageprotocol.h"

/**
 * @brief The Client class manages the actions of a client.
 * @details This Class manages starting, sending requests and recieving files.
 *
 */
class Client
{
public:
    Client(std::string serverAddress, int serverPort, int bufferSize,
           int SocketType, int protocol);
    ~Client();

    /**
     * @brief Initiate the client.
     * @throws SocketException
     */
    void initiate();

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
    bool sendMessage(MessageProtocol &message);

    /**
     * @brief Read message from the network and extracts the command and data.
     * @return A message protocol with appropriate command and data.
     * @throws SocketException
     */
    MessageProtocol readMessage();

    /**
     * @brief Send a command to server.
     * @param command Command name to send.
     * @param data optional data.
     * @return Response from Server.
     * @details This method handles commands to the server. depending
     *  on the command,it may contains data which is writtend to optional
     *  data[] array. After sending each command to the server, it will
     *  return a response which can be a message or Error message.
     */
    std::string sendCommand(std::string command, std::string data[]= nullptr);

    /**
     * @brief Recieve a file in chunks of byte based on buffer size.
     * @param fileName Recieved File name.
     * @return A response string. It could be success or Error message.
     */
    std::string recieveFile(std::string fileName);

    bool connect();

    /**
     * @brief Helper function to handle login request.
     * @param userInfo A string containng a serialized user class
     * @return a Response string, it could be success or Error message.
     * @throws SocketException
     */
    std::string login(std::string userInfo[]);

    /**
     * @brief Helper function to handle logout request.
     * @param userInfo A string containng a serialized user class
     * @return a Response string, it could be success or Error message.
     * @throws SocketException
     */
    std::string logout();

    /**
     * @brief Close the client.
     */
    void close();

    //  Setters
    void setOutStream(std::ostream &outStream);
    void setInStream(std::istream &inStream);



private:

    ClientInterface * clientInfrastructure;
    Console *console;

};

#endif // CLIENT_H
