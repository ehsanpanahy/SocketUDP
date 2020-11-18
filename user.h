#ifndef USER_H
#define USER_H

#include <string>
#include <cereal/archives/json.hpp>

using namespace std;

/**
 * @brief The User class is used to load, save and compare the login information.
 * @details This class handles the operation of load, save, compare the login
 *  infromation that comes to the server. it hashes the password field by MD5
 *  algorithm.
 */
class User
{
public:
    User();
    User(string userName, string password);
    ~User();


    /**
     * @brief equals compares two user class
     * @param other the User information
     * @return true if two users have the same username and password, otherwise
     *  false.
     */
    bool equals(const User &other);

    /**
     * this method is necessary for cereal library to work properly.
     */
    template<class Archive>
    void serialize(Archive & archive)
    {
      archive( userName, hashedPassword );
    }

    /**
     * @brief convert user class to a string to be sent over network.
     * @param os the output stream that accept the serialized user information.
     */
    void serializeUser(std::ostream &os);

    /**
     * @brief it retrieves the user info from a string.
     * @param is the input stream which has the user info.
     */
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
