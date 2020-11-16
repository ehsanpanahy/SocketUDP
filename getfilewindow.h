#ifndef GETFILEWINDOW_H
#define GETFILEWINDOW_H

#include <QDialog>
#include <QWidget>
#include "client.h"

namespace Ui {
class getfileWindow;
}

class getfileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit getfileWindow(Client &client, QWidget *parent = nullptr);
    ~getfileWindow();

protected:
    void showEvent(QShowEvent *event);

    public
        slots:
            void getFile();

private:
    Ui::getfileWindow *ui;
    Client *client;
};

#endif // GETFILEWINDOW_H
