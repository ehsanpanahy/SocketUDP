#include "syncinput.h"


SyncInput::SyncInput(std::istream &is)
{
    setStream(is);
}

SyncInput::~SyncInput()
{

}

void SyncInput::setStream(std::istream &stream)
{
    is = &stream;
}


void SyncInput::read(std::string &data)
{
    mu.lock();
    *is >> data;
    mu.unlock();

}

void SyncInput::readLine(std::string &data)
{
    mu.lock();
    std::getline(*is, data);
    mu.unlock();


}
