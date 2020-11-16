#ifndef USER_H
#define USER_H

#include <string>


using namespace std;

class User
{
public:
    User();
    User(string userName, string password);
    ~User();


    bool equals(const User &other);

    void serializeUser(std::ostream &os);
    void deSerializedUser(std::istream &is, int length);

    void setHashedPassword(const string &value);
    string getUserName() const;

    void setUserName(const string &value);
    string getHashedPassword() const;

private:
    string userName;
    string hashedPassword;
};

#endif // USER_H
