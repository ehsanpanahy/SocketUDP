#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include <QWidget>

#include "loginview.h"
#include "getfilewindow.h"
#include <sstream>

class QPushButton;

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(Client &client, QWidget *parent = nullptr);
    ~MainWindow();

public

    slots:
        void loginSlot();
        void quitSlot();
        void getFileSlot();
        void logoutSlot();


private:
        void writeLog();


private:
    Ui::MainWindow *ui;
    Client *client;
    LoginView *loginView;
    getfileWindow *getFileView;
    std::ostringstream* logStream;

};

#endif // FORM_H
