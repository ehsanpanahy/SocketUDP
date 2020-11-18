#include "console.h"
#include <ctime>


Console::Console(std::ostream &os, std::istream &is)
{
    setOutputStream(os);
    setInputStream(is);
}

Console::~Console()
{

}

void Console::write( std::string data)
{
    *os<<data;
}

void Console::writeLine(std::string data)
{
    *os<<data<<std::endl;
}

void Console::writeLineWithDate(std::string data)
{
    *os<<getCurrentDate();
    *os<<data;
}

void Console::writeSync(std::string data)
{
    writeMutex->lock();
    *os<<data;
    writeMutex->unlock();
}

void Console::writeLineSync(std::string data)
{
    writeMutex->lock();
    *os<<data<<std::endl;
    writeMutex->unlock();
}

void Console::writeLineWithDateSync(std::string data)
{
    writeMutex->lock();
    *os<<getCurrentDate();
    *os<<data;
    writeMutex->unlock();
}

void Console::read(std::string &data)
{
    *is >> data;
}

void Console::readLine(std::string &data)
{
    std::getline(*is, data);
}

void Console::readSync(std::string &data)
{
    readMutex->lock();
    *is >> data;
    readMutex->lock();
}

void Console::readLineSync(std::string &data)
{
    readMutex->lock();
    std::getline(*is, data);
    readMutex->lock();
}

void Console::setOutputStream(std::ostream &out)
{
    this->os = &out;
}

void Console::setInputStream(std::istream &in)
{
    this->is = &in;

}


std::string Console::getCurrentDate()
{
    std::time_t now = std::time(nullptr);
    return  std::asctime(std::localtime(&now));
}

void Console::setWriteMutex(std::mutex *value)
{
    writeMutex = value;
}


void Console::setReadMutex(std::mutex *value)
{
    readMutex = value;
}



