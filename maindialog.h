#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "loginview.h"
#include "getfilewindow.h"
#include <sstream>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(Client &client, QWidget *parent = nullptr);
    ~MainDialog();

    public

        slots:
            void loginSlot();
            void quitSlot();
            void getFileSlot();
            void logoutSlot();


    private:
            void writeLog();

private:
    Ui::MainDialog *ui;
    Client *client;
    LoginView *loginView;
    getfileWindow *getFileView;
    std::ostringstream* logStream;
};

#endif // MAINDIALOG_H
