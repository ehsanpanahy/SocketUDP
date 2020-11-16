#include "loginview.h"
#include "ui_loginview.h"
#include <string>
#include <iostream>
#include "md5.h"

using namespace std;


LoginView::LoginView(Client &client, QWidget *parent)
    :QDialog(parent),
    ui(new Ui::LoginView)
{

    ui->setupUi(this);

    this->client = &client;
    connect(ui->loginButton, SIGNAL(clicked()),  this,
            SLOT(loginSubmit()));

}

LoginView::~LoginView()
{
    delete ui;

}

void LoginView::showEvent(QShowEvent *event)
{
    ui->username_text->clear();
    ui->password_text->clear();
}

void LoginView::loginSubmit()
{
    string userInfo[2];
    userInfo[0].assign( ui->username_text->text().toUtf8().constData());
    userInfo[1].assign( ui->password_text->text().toUtf8().constData());

    userInfo[1] = md5(userInfo[1]);
    string response = client->sendCommand("login", userInfo);
    this->close();

}
