#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <vector>

class MessageProtocol
{
public:
    MessageProtocol();
    MessageProtocol(std::string message);
    MessageProtocol(int argc, std::string argv[]);
    ~MessageProtocol();


    std::string serializeMessage();
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
    ssize_t size;
};

#endif // MESSAGE_H
