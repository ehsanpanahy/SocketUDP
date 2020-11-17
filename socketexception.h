#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <stdexcept>


class SocketException : public std::runtime_error
{
public:
    SocketException();
    SocketException(std::string message, std::string action );

    std::string getAction() const;
    void setAction(const std::string &value);

private:
    std::string action;

};

#endif // SOCKETEXCEPTION_H
