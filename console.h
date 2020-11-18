#ifndef SYNCOUTPUT_H
#define SYNCOUTPUT_H

#include <iostream>
#include <mutex>

/**
 * @brief The Console class manages input-output interaction of
 * client-server classes.
 * @details It provides different streams for output and input. This way,
 *  it decouple the streams from Server and Client address, which can be
 *  set easily outside class.
 *
 */
class Console
{
public:
    Console() = delete;
    Console(std::ostream &os, std::istream &is);
    ~Console();

    /**
     * @brief Write to output
     * @param data message to write
     */
    void write(std::string data);

    /**
     * @brief Write a line to output.
     * @param data message to write
     */
    void writeLine(std::string data);

    /**
     * @brief Write output with a date-time tag.
     * @param data message to write
     */
    void writeLineWithDate(std::string data);

    /**
     * @brief Write to output with a mutex lock.
     * @param data message to write
     */
    void writeSync(std::string data);

    /**
     * @brief Write a line to output with a mutex lock.
     * @param data message to write
     */
    void writeLineSync(std::string data);

    /**
     * @brief Write output with a date-time tag and a mutex lock.
     * @param data message to write
     */
    void writeLineWithDateSync(std::string data);

    /**
     * @brief Read a word from input.
     * @param data container to store readed word.
     */
    void read(std::string &data);

    /**
     * @brief Read a line from input.
     * @param data container to store readed Line.
     */
    void readLine(std::string &data);

    /**
     * @brief Read a word from input with a mutex lock.
     * @param data container to store readed word.
     */
    void readSync(std::string &data);

    /**
     * @brief Read a line from input with a mutex lock.
     * @param data container to store readed Line.
     */
    void readLineSync(std::string &data);

    //  Setters
    void setOutputStream(std::ostream &out);
    void setInputStream(std::istream &in);

    void setReadMutex(std::mutex *value);
    void setWriteMutex(std::mutex *value);

private:
    std::string getCurrentDate();

private:
    std::mutex *readMutex;
    std::mutex *writeMutex;
    std::ostream* os;
    std::istream *is;

};


#endif // SYNCOUTPUT_H
