#include "getfilewindow.h"
#include "ui_getfilewindow.h"
#include "string"

using namespace std;

getfileWindow::getfileWindow(Client &client, QWidget *parent)
   :QDialog(parent),
    ui(new Ui::getfileWindow)
{
    ui->setupUi(this);

    this->client = &client;

    connect(ui->getfile_Button, SIGNAL(clicked()), this ,
            SLOT(getFile()));

}

getfileWindow::~getfileWindow()
{
    delete ui;
}

void getfileWindow::showEvent(QShowEvent *event)
{
    ui->filename_text->clear();
}

void getfileWindow::getFile()
{
    string fileName[1];
    fileName[0].assign(ui->filename_text->text().toUtf8().constData());
    string response = client->sendCommand("getfile", fileName);
    this->close();
}

