#ifndef USER_H
#define USER_H

#include <string>
#include <cereal/archives/json.hpp>

using namespace std;

class User
{
public:
    User();
    User(string userName, string password);
    ~User();


    bool equals(const User &other);

    template<class Archive>
    void serialize(Archive & archive)
    {
      archive( userName, hashedPassword );
    }

    void serializeUser(std::ostream &os);
    void deSerializedUser(std::istream &is);

    void setHashedPassword(const string &value);
    string getUserName() const;

    void setUserName(const string &value);
    string getHashedPassword() const;

private:
    string userName;
    string hashedPassword;
};

#endif // USER_H
