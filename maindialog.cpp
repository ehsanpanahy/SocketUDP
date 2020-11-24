#include "maindialog.h"
#include "ui_maindialog.h"

using namespace std;

MainDialog::MainDialog(Client &client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
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

MainDialog::~MainDialog()
{
    delete ui;
    delete loginView;
    delete getFileView;
    delete logStream;
}

void MainDialog::loginSlot()
{
    loginView->show();
    loginView->exec();
    writeLog();
}

void MainDialog::quitSlot()
{
    client->sendCommand("quit");
    this->close();

}

void MainDialog::getFileSlot()
{
    getFileView->show();
    getFileView->exec();
    writeLog();

}

void MainDialog::logoutSlot()
{
    string response = client->sendCommand("logout");
    writeLog();

}

void MainDialog::writeLog()
{
    ui->status_Text->append(logStream->str().c_str());
    logStream->str("");

}
