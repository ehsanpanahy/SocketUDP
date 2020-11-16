#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include "client.h"

#include <QDialog>
#include <QWidget>

namespace Ui {
class LoginView;
}

class LoginView : public QDialog
{
    Q_OBJECT

public:
    explicit LoginView(Client &client, QWidget *parent = nullptr );
    ~LoginView();

protected:
    void showEvent(QShowEvent* event);

    public
        slots:
            void loginSubmit();

private:
    Ui::LoginView *ui;
    Client *client;

};

#endif // LOGINVIEW_H
