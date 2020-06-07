#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QMessageBox>

namespace Ui {
class LogInWindow;
}

class LogInWindow : public QDialog
{
    Q_OBJECT

public:
    explicit    LogInWindow(QWidget *parent = nullptr);
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
};

#endif // LOGINWINDOW_H
