#ifndef SYNCINPUT_H
#define SYNCINPUT_H
#include <mutex>
#include <iostream>

class SyncInput
{
public:
    SyncInput() = delete;
    SyncInput(std::istream &is);
    ~SyncInput();

    void read(std::string &data);
    void readLine(std::string &data);

    void setStream(std::istream &stream);

private:

    std::mutex mu;
    std::istream *is;

};

#endif // SYNCINPUT_H
