#include "user.h"
#include "md5.h"
#include "user.h"

#include <regex>
#include <iostream>
#include <algorithm>


User::User()
{

}

User::User(string userName, string password)
    :userName(userName)
{
    this->hashedPassword = md5(password);
}

User::~User()
{

}

bool User::equals(const User &other)
{
    if (this == &other) return true;

    if (this->userName.compare(other.getUserName()) !=0)
        return false;

    if (this->hashedPassword.compare(other.getHashedPassword()) != 0)
        return false;

    return true;
}

void User::serializeUser(ostream &os)
{

    string serial;

    serial.append("[\n\t\"user\":{\n\t\t\"username\": ");
    serial.append("\"" + this->getUserName() + "\"" + ",\n");
    serial.append("\t\t\"hashedPassword\": \"" + this->getHashedPassword()+ "\"");
    serial.append("\n\t}").append("\n]");

    os.write(serial.c_str(), serial.length());
}

void User::deSerializedUser(istream &is, int length)
{
    string sUser;
    char buffer[length];
    is.read(buffer, length);

    sUser.assign(buffer);
    vector<string> elemnts;
    std::regex pattern("\"(.*?)\"");

    vector<string> elements;
    smatch match;
    while(std::regex_search(sUser, match, pattern))
    {
        for (auto x : match)
            elemnts.push_back(x.str());
        sUser = match.suffix().str();
    }

    this->userName = elemnts[5];
    this->hashedPassword = elemnts[9];
}


string User::getUserName() const
{
    return userName;
}

void User::setUserName(const string &value)
{
    userName = value;
}

string User::getHashedPassword() const
{
    return hashedPassword;
}
void User::setHashedPassword(const string &value)
{
    hashedPassword = value;
}

