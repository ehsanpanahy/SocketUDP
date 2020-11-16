#ifndef SYNCOUTPUT_H
#define SYNCOUTPUT_H

#include <iostream>
#include <mutex>

class SyncOutput
{
public:
    SyncOutput() = delete;
    SyncOutput(std::ostream &os);
    ~SyncOutput();
    void write(std::string data);
    void writeLine(std::string data);
    void writeLineWithDate(std::string data);

    void setStream(std::ostream &out);

private:
    std::string getCurrentDate();
private:
    std::mutex mu;
    std::ostream* os;

};


#endif // SYNCOUTPUT_H
