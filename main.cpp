#include <iostream>
#include "server.h"
#include "client.h"
#include <thread>
#include "commons.h"
#include <string>
#include <fstream>

#include "commandlineinterface.h"

#include <QApplication>
#include "mainwinow.h"

using namespace std;

#define BUFFER_SIZE 1024



int main(int argc, char *argv[])
{
    string addrrss = "127.0.0.1";
    int port = 9734;

    Server* server = new Server(addrrss, port, BUFFER_SIZE,
                                Commons::UDP_SOCKET, 0);
    Client* client = new Client(addrrss, port, BUFFER_SIZE,
                                Commons::UDP_SOCKET, 0);

    server->initiate();
    client->initiate();

    ofstream outLogStream("Server.log");

    server->setOutStream(outLogStream);
    client->setOutStream(cout);

    //CommandLineInterface *cmd = new CommandLineInterface(*client);


    thread s(&Server::startServer, server);
    //thread c(&CommandLineInterface::startClient, cmd);

//    c.join();
//    s.join();


    QApplication app(argc, argv);
    MainWindow *mainDialog = new MainWindow(*client);
    mainDialog->show();
    mainDialog->exec();


    s.join();

    delete client;
    delete server;

    return 0;

    //delete cmd;

}
