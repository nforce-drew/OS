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
        show();
        QMessageBox::information(this, "Logged", "User " + ((LogInWindow*)m_loginWndw)->getUserName() + " logged.");
    }

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
    if (m_lastStatus)
    {
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
    }

    m_lastStatus = false;
//    delete m_pTcpSocket;
//    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(m_strHost, m_nPort);
}
// ----------------------------------------------------------------------
void MyClient::slotSendFilesToServer()
{
    QStringList fPaths; // Нужно передать сюда пути к файлом для передачи задачи на сервер
    QFileInfo*  p_fileInfo;
    QFile*      p_file;
    QByteArray  arrBlock;
    QByteArray  fileData;
    MainHeader  mainHeader;
    FileHeader  fileHeader;
    QDataStream out(&arrBlock, QIODevice::ReadWrite);

    qDebug() << "Why send files";
    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);
    fPaths << "/home/nforce/Desktop/AllDesktop/Конспект_24.03.pdf"
           << "/home/nforce/Desktop/AllDesktop/crock.jpg";// Удалить
    out.writeRawData((char*)&mainHeader, sizeof(MainHeader));
    for (int i = 0; i < fPaths.size(); i++)
    {
        p_file = new QFile(fPaths[i]);
        if(!p_file->open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, "Error", "File " + fPaths[i] + " does not open!");
            qDebug() << "---Файл " << fPaths[i] << " не открыт!!!";
            return;
        }
        fileData.clear();
        fileData = p_file->readAll();
        p_fileInfo = new QFileInfo(*p_file);
        fileHeader.setData(unsigned(p_fileInfo->size()), (char*)p_fileInfo->fileName().toStdString().data());
        out.writeRawData((char*)&fileHeader, sizeof(FileHeader));
        out.writeRawData(fileData.data(), fileData.size());
        p_file->close();
        delete p_fileInfo;
        delete p_file;
    }
    out.device()->seek(0);
    mainHeader.setData(arrBlock.size(), fPaths.size(), SEND_FILES);
    out.writeRawData((char*)&mainHeader, sizeof(MainHeader));
    m_pTcpSocket->write(arrBlock);
    qDebug() << "Bytes sent: " << arrBlock.size();
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
    qDebug() << bytes(arrBlock.data(), arrBlock.size());
    m_pTcpSocket->write(arrBlock);
}
// ------------------------------------------------------------------
void MyClient::slotConnected()
{
    m_lastStatus = true;
    m_ptxtInfo->append("Received the connected() signal");
}

MyClient::~MyClient()
{
    delete ui;
}


