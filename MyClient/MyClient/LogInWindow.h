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
    void        connectDatabase();
    QString     getUserName();
    ~LogInWindow();

private:
    Ui::LogInWindow*    ui;
    QSqlDatabase        db;
    QString             m_userName;

signals:
    void logged();


public slots:
    void slotCheckLogin();
    void slotIncorrectLogin();
};

#endif // LOGINWINDOW_H
