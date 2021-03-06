#ifndef MYCLIENT_H
#define MYCLIENT_H

#include "MainHeader.h"
#include "FileHeader.h"
#include "LogInWindow.h"
#include "Headers.h"
#include "DropArea.h"
#include "TaskStateHeader.h"
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
#include <QTimer>
#include <QFileDialog>

//=================================================================================
namespace Ui {
class MyClient;
}

class MyClient : public QWidget
{
    Q_OBJECT

private:
    QTcpSocket*     m_pTcpSocket;
    QTextEdit*      m_ptxtInfo;
    QLineEdit*      m_ptxtInput;
    void*           m_loginWndw;
    QString         m_strHost;
    int             m_nPort;
    bool            m_lastStatus;
    QString         m_userName;
    QList<TaskStateHeader> m_tasksList;
    QString         m_dirToSave;
    QList<FileHeader> m_binsInfo;

public:
    MyClient(const QString& strHost, int nPort, QWidget *pwgt = 0);
    ~MyClient();

private slots:
    void slotReadyRead();                               //Принятие данных
    void slotError(QAbstractSocket::SocketError err);   //Ошибка подключения с сервером
    void slotSendFilesToServer();                            //Отправка файлов
    void slotConnected();                               //Клиент подключился к серверу
    void slotReconnect();
    void slotDroppedFiles(QStringList newFiles);
    void slotCancelClicked();
    void slotDownloadClicked();
    void slotSolveClicked();
    void setDeleteBtnFileEnable();
    void deleteFileClicked();
public:
    void slotSendMainHdrToServer(TYPE dataType, unsigned num);
    void slotSendDataToServer(TYPE dataType, char* data, unsigned len); //Отправка данных или запроса
                                                                         // если дополнительные данные не передаются,
                                                                          //то присвоить data = NULL и len = 0
private:
    void setTasksList(QList<TaskStateHeader> &tasksList);
    void successRecieve();
    unsigned getBinId(int index);

private:
    Ui::MyClient *ui;
};

#endif // MYCLIENT_H
