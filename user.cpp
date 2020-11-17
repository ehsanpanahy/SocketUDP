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
    User u;
    u.setUserName(this->userName);
    u.setHashedPassword(this->hashedPassword);

    cereal::JSONOutputArchive outAr(os);
    outAr(u);

}

void User::deSerializedUser(istream &is)
{
    cereal::JSONInputArchive isAr(is);
    User u;
    isAr(u);
    this->userName = u.getUserName();
    this->hashedPassword = u.getHashedPassword();

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

