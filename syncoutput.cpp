#include "syncoutput.h"
#include <ctime>

void SyncOutput::write( std::string data)
{

    mu.lock();
    *os<<data;
    mu.unlock();
}

void SyncOutput::writeLine(std::string data)
{

    mu.lock();
    *os<<data<<std::endl;
    mu.unlock();
}

void SyncOutput::writeLineWithDate(std::string data)
{
    mu.lock();
    *os<<getCurrentDate();
    *os<<data;
    mu.unlock();
}

void SyncOutput::setStream(std::ostream &out)
{
    os = &out;
}

std::string SyncOutput::getCurrentDate()
{
    std::time_t now = std::time(nullptr);
    return  std::asctime(std::localtime(&now));
}


SyncOutput::SyncOutput(std::ostream &os)
{

    setStream(os);
}

SyncOutput::~SyncOutput()
{

}
