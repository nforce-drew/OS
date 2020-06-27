#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QMessageBox>
#include <string>
#include "MyClient.h"
#include "Headers.h"

namespace Ui {
class LogInWindow;
}

class LogInWindow : public QDialog
{
    Q_OBJECT

public:
    LogInWindow();
    LogInWindow(QWidget *parent = nullptr);
    QString     getUserName();
    ~LogInWindow();

private:
    Ui::LogInWindow*    ui;
    QString             m_userName;
    bool                m_isSignIn;

signals:
    void logged();


public slots:
    void slotCheckLogin();
    void slotIncorrectLogin();
    void changeToSignUp();
    void changeToSignIn();
private slots:
    void slotCancelClicked();
};

#endif // LOGINWINDOW_H
