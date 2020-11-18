#include <termios.h>

#include "commandlineinterface.h"
#include "md5.h"


using namespace std;

CommandLineInterface::CommandLineInterface(Client &client)
{

    this->client = &client;
}

void CommandLineInterface::startClient()
{
    cout << endl << "Client<<Starting client..." << endl;
    string command;
    string response;
    while(1)
    {
        cout<<"Here is a list of valid commands:"<<endl;
        cout <<"\t1)Login"<<endl << "\t2)getfile" << endl <<"\t3)logout"
            <<endl <<"type quit to exit the program" << endl;
        cout <<"Enter command:";
        cin>> command;
        response = commandInterpreter(command);
        if (response.compare("quit") == 0)
        {
            cout <<"Shutting client down..."<<endl;;
            break;
        }
        cout <<response<<endl;
    }
}

string CommandLineInterface::commandInterpreter(string &command)
{
    string response;

    if (command.compare("login") == 0)
    {
        string userInfo[2];
        cout <<"Enter username:";
        cin >> userInfo[0];
        cout <<"Enter Password:";
        string password;
        getPassword(password);
        userInfo[1] = md5(password);
        response = client->sendCommand("login", userInfo);

    }
    else if(command.compare("getfile") == 0)
    {
        string fileName[1];
        cout <<"Enter file name:";
        cin >>fileName[0];
        response = client->sendCommand("getfile", fileName);

    }
    else if (command.compare("logout") ==0)
    {
        response = client->sendCommand("logout");

    }
    else if(command.compare("quit") ==0 )
    {
        client->sendCommand("quit");
        response = "quit";
    }
    else
    {
        response = "Bad input command";
    }

    return response;
}

void CommandLineInterface::getPassword(string &password)
{
    struct termios initialrsettings, newrsettings;

    //  get the default settings of terminal
    tcgetattr(fileno(stdin), &initialrsettings);

    //  save settings in a new variable so we can easily apply them to terminal.
    newrsettings = initialrsettings;

    //  change setting to preferred options.
    newrsettings.c_lflag &= ~ECHO;

    //  apply changes to terminal
    tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings);
    cin >>password;

    //  Reset terminal setting to default.
    tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);

}











