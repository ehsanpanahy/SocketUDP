#include "socketexception.h"

using namespace std;

SocketException::SocketException(string message, string action)
    :runtime_error(message)
{
    this->action = action;
}

std::string SocketException::getAction() const
{
    return action;
}

void SocketException::setAction(const std::string &value)
{
    action = value;
}
