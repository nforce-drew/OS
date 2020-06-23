#include "MyClient.h"
#include "ui_MyClient.h"
#include <string.h>
#include <string>

QString bytes(const char *buf, int size)
{
    QString message;
    for (int i = 0; i < size; i++)
    {
        message += QString::number((int)buf[i]) + " ";
        if ((i + 1) % 4 == 0)
            message += "| ";
    }
    return (message);
}

MyClient::MyClient(const QString& strHost, int nPort, QWidget *pwgt/*=0*/) :
    QWidget(pwgt),
    ui(new Ui::MyClient),
    m_nNextBlockSize(0)
{
//    setWindowIcon(QIcon(":/Images/Images/user.png"));
    m_lastStatus = true;
    m_pTcpSocket = new QTcpSocket(this);

    //-------------
    m_strHost = strHost;
    m_nPort = nPort;
    //-------------
    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError))
           );



    m_ptxtInfo  = new QTextEdit;
    m_ptxtInput = new QLineEdit;

//    connect(m_ptxtInput, SIGNAL(returnPressed()),
//            this,        SLOT(slotSendFilesToServer())
//           );
    m_ptxtInfo->setReadOnly(true);

    QPushButton* sendButton = new QPushButton("&Send");
    connect(sendButton, SIGNAL(clicked()), SLOT(slotSendFilesToServer()));

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
    pvbxLayout->addWidget(m_ptxtInput);
    pvbxLayout->addWidget(sendButton);
    m_loginWndw = new LogInWindow(this);
    if (((LogInWindow*)m_loginWndw)->exec() == QDialog::Accepted)
    {
        qDebug() << "User " + ((LogInWindow*)m_loginWndw)->getUserName() + " logged.";
//        show();
        QMessageBox::information(this, "Logged", "User " + ((LogInWindow*)m_loginWndw)->getUserName() + " logged.");
    }
    m_userName = ((LogInWindow*)m_loginWndw)->getUserName();
    qDebug() << "logged: " << m_userName;


//    m_loginWndw->show();

    setLayout(pvbxLayout);
}

// ----------------------------------------------------------------------
void MyClient::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    QByteArray  data;
    MainHeader  mainHeader;
    FileHeader  fileHeader;

    qDebug() << "Receiving data...";
    if (m_pTcpSocket->bytesAvailable() < sizeof(MainHeader))
    {
        qDebug() << "Error reading data.";
//        QMessageBox::critical(this, "Ошибка", "Ошибка чтения данных!");
        return;
    }
    in.readRawData((char*)&mainHeader, sizeof(MainHeader));
    while (m_pTcpSocket->bytesAvailable() <
                        qint64(mainHeader.getMsgSize() - sizeof(MainHeader)))
        if (!m_pTcpSocket->waitForReadyRead(1000))
        {
            qDebug() << "Error: reading data.";
//            QMessageBox::critical(this, "Ошибка", "Ошибка чтения данных!");
            return;
        }
    //Если пришли файлы:
    if (mainHeader.getType() == SEND_FILES)
    {
        for (int i = 0; i < mainHeader.getCount(); i++)
        {
            in.readRawData((char*)&fileHeader, sizeof(FileHeader));
            qDebug() << "FileHeader: " << fileHeader.getFileSize() << " " << fileHeader.getFileName();
            data.resize(fileHeader.getFileSize());
            in.readRawData(data.data(), data.size());

            //путь для сохранения
            QFile file("/home/nforce/Desktop/ClientReceive/" + QString(fileHeader.getFileName()));
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Truncate))
            {
                qDebug() << "Error: opening the file for writing "
                            << "/home/nforce/Desktop/ClientReceive/" << fileHeader.getFileName();
                QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи!");
            }
            file.write(data);
            file.close();
        }
    }
    //Если пришли другие данные:
    if (mainHeader.getType() == PERMISSION_LOGIN)
    {
        qDebug() << "PERMISSION_LOGIN";
        ((LogInWindow*)m_loginWndw)->hide();
        show();
    }
    if (mainHeader.getType() == BAN_LOGIN)
    {
        qDebug() << "BAN_LOGIN";
        ((LogInWindow*)m_loginWndw)->slotIncorrectLogin();
    }
    if (mainHeader.getType() == QUEUE_LIST)
    {
        data.clear();
        data.reserve(mainHeader.getMsgSize() - sizeof(MainHeader));
        qDebug() << mainHeader.getMsgSize() << " " << mainHeader.getCount() << " " << mainHeader.getType();
        qDebug() << in.readRawData(data.data(), mainHeader.getMsgSize() - sizeof(MainHeader));
    }
    qDebug() << "End of data reading.";
}

// ----------------------------------------------------------------------
void MyClient::slotError(QAbstractSocket::SocketError err)
{

//    if (m_lastStatus)
//    {
        QString strError =
                "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                                 "The host was not found." :
                                 err == QAbstractSocket::RemoteHostClosedError ?
                                     "The remote host is closed." :
                                     err == QAbstractSocket::ConnectionRefusedError ?
                                         "The connection was refused." :
                                         QString(m_pTcpSocket->errorString())
                                         );
        m_ptxtInfo->append(strError);
        m_pTcpSocket->close();
        QTimer::singleShot(0, this, SLOT(slotReconnect()));
//    }

//    m_lastStatus = false;
//    delete m_pTcpSocket;
//    m_pTcpSocket = new QTcpSocket(this);
//    m_pTcpSocket->connectToHost(m_strHost, m_nPort);
}
// ----------------------------------------------------------------------
void MyClient::slotReconnect()
{
//    qDebug() << "reconnect";
    m_pTcpSocket->connectToHost(m_strHost, m_nPort);
}
// ----------------------------------------------------------------------
void MyClient::slotSendFilesToServer()
{
    QStringList fPaths; // Нужно передать сюда пути к файлом для передачи задачи на сервер
    QFileInfo*  p_fileInfo;
    QFile*      p_file;
    QByteArray  arrBlock;
    MainHeader  mainHeader;
    FileHeader  fileHeader;
    QDataStream out(&arrBlock, QIODevice::ReadWrite);
    unsigned    msgSize;
    QVector<QVector<QString>>   filesInfo;
    QVector<QString>            info;
    qint64                      totalSent(0);
    int                         readBytes;

    qDebug() << "Why send files";
    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);
    fPaths << "/home/nspace/Desktop/AllDesktop/Dzheremi.djvu"
           << "/home/nspace/Desktop/AllDesktop/scrn29.png"
           << "/home/nspace/Desktop/AllDesktop/Конспект_24.03.pdf"
           << "/home/nspace/Desktop/AllDesktop/crock.jpg";// Удалить
    msgSize = sizeof(MainHeader);
    for (QString path : fPaths)
    {
        info.clear();
        p_file = new QFile(path);
        if(!p_file->open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, "Error", "File " + path + " does not open!");
            qDebug() << "---Файл " << path << " не открыт!!!";
            return;
        }
        p_fileInfo = new QFileInfo(*p_file);
        msgSize += sizeof(FileHeader);
        msgSize += p_fileInfo->size();
        info.push_back(QString::number(p_fileInfo->size()));
        info.push_back(p_fileInfo->fileName());
        filesInfo.push_back(info);
        p_file->close();
        delete p_fileInfo;
        delete p_file;
    }
    qDebug() << "msgSize = " << msgSize;
    mainHeader.setData(msgSize, fPaths.size(), SEND_FILES);
    arrBlock.clear();
    out.device()->seek(0);
    out.writeRawData((char*)&mainHeader, sizeof(MainHeader));
    totalSent = m_pTcpSocket->write(arrBlock);
    qDebug() << "sent =" << totalSent;
    for (int i = 0; i < fPaths.size(); i++)
    {
        p_file = new QFile(fPaths[i]);
        if(!p_file->open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, "Error", "File " + fPaths[i] + " does not open!");
            qDebug() << "---Файл " << fPaths[i] << " не открыт!!!";
            return;
        }
        arrBlock.clear();
        fileHeader.setData(unsigned(filesInfo[i][0].toInt()), (char*)filesInfo[i][1].toStdString().data());
        qDebug() << fileHeader.getFileSize() << fileHeader.getFileName();
        out.device()->seek(0);
        out.writeRawData((char*)&fileHeader, sizeof(FileHeader));
        totalSent = m_pTcpSocket->write(arrBlock);
        qDebug() << "sent =" << totalSent;
        readBytes = 1;
//        int j = 0;
        while (readBytes > 0)
        {
            arrBlock.clear();
//            p_file->seek(j * 1024);
            arrBlock = p_file->read(1024);

            qDebug() << "Read bytes =" << arrBlock.size();
            readBytes = arrBlock.size();
            if (readBytes > 0)
            {
                out.device()->seek(0);
                out.writeRawData(arrBlock.data(), arrBlock.size());
                totalSent = m_pTcpSocket->write(arrBlock);
                qDebug() << "sent =" << totalSent;
            }
//            j++;
        }
        p_file->close();
        delete p_file;
    }
//    out.device()->seek(0);
//    mainHeader.setData(arrBlock.size(), fPaths.size(), SEND_FILES);
//    out.writeRawData((char*)&mainHeader, sizeof(MainHeader));
//    m_pTcpSocket->write(arrBlock);
    qDebug() << "Bytes sent: " << totalSent;
}
// ------------------------------------------------------------------
void MyClient::slotSendDataToServer(TYPE dataType, char* data, unsigned len)
{
    MainHeader mainHdr;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::ReadWrite);

    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);
    mainHdr.setData(sizeof(MainHeader) + len, 0, dataType);
    out.writeRawData((char*)&mainHdr, sizeof(MainHeader));
    if (data != NULL && len != 0)
        out.writeRawData(data, len);
    m_pTcpSocket->write(arrBlock);
}
// ------------------------------------------------------------------
void MyClient::slotConnected()
{
    m_lastStatus = true;
    if (m_userName.size() != 0)
    {
        slotSendDataToServer(RECONNECT, (char*)m_userName.toStdString().c_str(), m_userName.size() + 1);
    }

    m_ptxtInfo->append("Received the connected() signal");
}

MyClient::~MyClient()
{
    delete ui;
}


