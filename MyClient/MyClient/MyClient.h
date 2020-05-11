#ifndef MYCLIENT_H
#define MYCLIENT_H

#include "MainHeader.h"
#include "FileHeader.h"
#include <QWidget>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>

//=================================================================================
namespace Ui {
class MyClient;
}

class MyClient : public QWidget
{
    Q_OBJECT

private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit*  m_ptxtInfo;
    QLineEdit*  m_ptxtInput;
    quint16     m_nNextBlockSize;
    QString     m_strHost;
    int         m_nPort;
    bool        m_lastStatus;

public:
    MyClient(const QString& strHost, int nPort, QWidget *pwgt = 0);
    ~MyClient();

private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotSendToServer();
    void slotConnected();

private:
    Ui::MyClient *ui;
};

#endif // MYCLIENT_H
