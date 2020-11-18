#include <iostream>
#include "server.h"
#include "client.h"
#include <thread>
#include "commons.h"
#include <string>
#include <fstream>
#include "socketexception.h"
#include "commandlineinterface.h"

#include <QApplication>
#include "mainwidnow.h"

using namespace std;

#define BUFFER_SIZE 1024

/**
 * @author Ehsan Panahi
 * @details A simple Server-Client application which runs in parallel threads.
 *  Client has two interfaces which can be used arbitary. One is a Command line
 *  interface which works well with linux terminal. the other one is a simple
 *  Qt Window interface.
 *
 */


int main(int argc, char *argv[])
{
    string addrrss = "127.0.0.1";
    int port = 9734;

    Server* server = new Server(addrrss, port, BUFFER_SIZE,
                                Commons::UDP_SOCKET, 0);
    Client* client = new Client(addrrss, port, BUFFER_SIZE,
                                Commons::UDP_SOCKET, 0);
    try {
        client->initiate();
        server->initiate();
    } catch (const SocketException &e) {
        cout <<"action:" + e.getAction() + "Failed with the message:"
            <<e.what();
        exit(EXIT_FAILURE);
    }

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
    //delete cmd;

    return 0;



}
