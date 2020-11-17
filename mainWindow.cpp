#include "mainwidnow.h"
#include "ui_form.h"
#include "loginview.h"
#include "getfilewindow.h"
#include "string"
#include <iostream>

using namespace std;

MainWindow::MainWindow(Client &client, QWidget *parent)
    :QDialog(parent), ui(new Ui::Form)
{

    ui->setupUi(this);

    connect(ui->loginButton, SIGNAL(clicked()),  this,
            SLOT(loginSlot()));
    connect(ui->quit_Button, SIGNAL(clicked()), this,
            SLOT(quitSlot()));
    connect(ui->logout_Button, SIGNAL(clicked()), this,
            SLOT(logoutSlot()));
    connect(ui->getfile_Button, SIGNAL(clicked()), this,
            SLOT(getFileSlot()));

    this->client = &client;
    loginView = new LoginView(client);
    getFileView = new getfileWindow(client);


    logStream = new ostringstream();
    client.setOutStream(*logStream);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete loginView;
    delete getFileView;
    delete logStream;


}

void MainWindow::loginSlot()
{
    loginView->show();
    loginView->exec();
    writeLog();

}

void MainWindow::quitSlot()
{
    client->sendCommand("quit");
    this->close();

}

void MainWindow::getFileSlot()
{
    getFileView->show();
    getFileView->exec();
    writeLog();

}

void MainWindow::logoutSlot()
{
    string response = client->sendCommand("logout");
    writeLog();
}

void MainWindow::writeLog()
{
    ui->status_Text->append(logStream->str().c_str());
    logStream->str("");
}
