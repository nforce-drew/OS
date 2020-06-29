#ifndef ADMIN_H
#define ADMIN_H

#include "TaskHeader.h"
#include "QueueTable.h"
#include "MainHeader.h"
#include "LoginHeader.h"
#include "FileHeader.h"
#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QTcpSocket>
#include <QTableWidgetItem>
#include <QFileDialog>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(const QString& strHost, int nPort, QWidget *parent = 0);
    ~Admin();

private:
    Ui::Admin *ui;
    QTcpSocket*     m_pTcpSocket;
    QString         m_strHost;
    int             m_nPort;
    bool            m_lastStatus;
    QList<QVector<QString>> m_usersInfo;
    QString         m_newBin;
signals:
    void reconnect();
private:
    void    setTable(QList<TaskHeader> queueList);
    void    setOnlineUsers(QStringList users);
    void    fillUserInfoTable(QList<QVector<QString>> list);
    void    fillUserNamesCmbBox(QList<QVector<QString>> list);
    void    fillBinsList(QStringList binsNames);

private slots:
//    void    slotQueueChanged();
    void deleteTask();
    void setEnabledDeleteBtn(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void slotSendQueue(QList<TaskHeader>* queueLst);
    void slotReconnect();

    void slotReadyRead();                               //Принятие данных
    void slotError(QAbstractSocket::SocketError err);   //Ошибка подключения с сервером
    void slotConnected();
    void slotSendMainHdrToServer(TYPE dataType, unsigned num);
    void slotSendBinToServer();
    void slotSendDataToServer(TYPE dataType, unsigned count, char* data, unsigned len); //Отправка данных или запроса
                                                                         // если дополнительные данные не передаются,
                                                                          //то присвоить data = NULL и len = 0
    void deleteUserBtnEnabled();
    void deleteUserBtnClicked();
    void editPasswordChanged(const QString &text);
    void editLoginChanged(const QString &text);
    void addBtnClicked();
    void editNewPasswordChanged(const QString &text);
    void comboBoxChanged(const QString &text);
    void newPassBtnClicked();

    void addBinBtnClicked();
};

#endif // ADMIN_H
