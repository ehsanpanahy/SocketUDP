#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <vector>

/**
 * @brief The MessageProtocol class defines a simple Messaging protocol for
 *  UDP socket.
 * @details Since UDP sockets does not support an inherent mechanism for
 *  exchanging messages over the network, we defined this simple message protocol
 *  to:
 *      1)send the predefined command name.
 *      2)remove unwanted characters from message.
 *  It adds the length of the message to the beginning of the text, and attach
 *  it with a delimiter.on the desitination side, it extracts the message by
 *  using of this dedicated length.
 *
 */

class MessageProtocol
{
public:
    MessageProtocol();

    /**
     * @brief MessageProtocol
     * @param message A simple message to send.
     */
    MessageProtocol(std::string message);

    /**
     * @brief MessageProtocol
     * @param argc dedicated number of data.
     * @param argv data to send
     */
    MessageProtocol(int argc, std::string argv[]);
    ~MessageProtocol();


    /**
     * @brief prepare message to be sent over the network.
     * @details this method attaches the length of the message and the command
     *  name to the begining of the Message.
     * @return A string with dedicated length.
     */
    std::string serializeMessage();

    /**
     * @brief  Retrive recieved message
     * @param message : Raw message recieved from Socket.
     * @details It will extract the command name and the dedicated message from
     *  incoming text.
     *
     */
    void deSerializeMessage(std::string message);


    std::string getCommand() const;
    void setCommand(const std::string &value);

    std::vector<std::string> getData() const;
    void addData(const std::string data);

    std::string getDelimiter() const;
    void setDelimiter(const std::string &value);



private:
    std::string command;
    std::string delimiter = "-";
    std::vector<std::string> data;
    unsigned long size;
};

#endif // MESSAGE_H
