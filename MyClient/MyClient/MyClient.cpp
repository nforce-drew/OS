#include "MyClient.h"
#include "ui_MyClient.h"
#include <string.h>

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

    connect(m_ptxtInput, SIGNAL(returnPressed()),
            this,        SLOT(slotSendToServer())
           );
    m_ptxtInfo->setReadOnly(true);

    QPushButton* pcmd = new QPushButton("&Send");
    connect(pcmd, SIGNAL(clicked()), SLOT(slotSendToServer()));

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
    pvbxLayout->addWidget(m_ptxtInput);
    pvbxLayout->addWidget(pcmd);
    setLayout(pvbxLayout);
}

// ----------------------------------------------------------------------
void MyClient::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_9);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16))
                break;
            in >> m_nNextBlockSize;
        }

        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize)
            break;

        QTime   time;
        QByteArray fileData;

        in >> fileData;


        QFile file("/home/nforce/Desktop/file2.txt");
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
            QMessageBox::critical(this, "Error", "File2 does not open!");
        file.write(fileData);

        m_ptxtInfo->append(time.toString() + ": " + QString::number(sizeof(m_nNextBlockSize) + fileData.size()));
        m_nNextBlockSize = 0;
    }
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
    m_pTcpSocket->connectToHost(m_strHost, m_nPort);
}

// ----------------------------------------------------------------------
void MyClient::slotSendToServer()
{
    QStringList fPaths; // Нужно передать сюда пути к файлом для передачи задачи на сервер
    QFileInfo*  p_fileInfo;
    QFile*      p_file;
    QByteArray  arrBlock;
    QByteArray  fileData;
    MainHeader  mainHeader;
    FileHeader  fileHeader;
    QDataStream out(&arrBlock, QIODevice::ReadWrite);

    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);
    fPaths << "/home/nforce/Desktop/scrn14.png"
               << "/home/nforce/Desktop/scrn15.png"
                   << "/home/nforce/Desktop/scrn16.png"
                       << "/home/nforce/Desktop/scrn17.png"
                           << "/home/nforce/Desktop/scrn18.png"; // Удалить
    out.writeRawData((char*)&mainHeader, sizeof(MainHeader));
    for (int i = 0; i < fPaths.size(); i++)
    {
        qDebug() << fPaths[i];
        p_file = new QFile(fPaths[i]);
        if(!p_file->open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, "Error", "File does not open!");
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
    int dat = m_pTcpSocket->write(arrBlock);
//    QMessageBox::information(this, "Message size", QString::number(arrBlock.size()));










//    QByteArray  arrBlock;
//    QByteArray  fileData;
//    QString     filePath("/home/nforce/Конспект_23.03.djvu");
//    QDataStream out(&arrBlock, QIODevice::ReadWrite);
//    QFile       file(filePath);
//    QFileInfo   fileInfo(filePath);
//    MainHeader  mainHeader(77, 2, SEND_FILES);
//    FileHeader  fileHeader;
//    int         dat;

//    out.setVersion(QDataStream::Qt_4_5);
//    out.setByteOrder(QDataStream::LittleEndian);

//    if(!file.open(QIODevice::ReadOnly))
//        QMessageBox::critical(this, "Error", "File does not open!");
//    fileData = file.readAll();
//    fileHeader.setData(unsigned(fileInfo.size()), (char*)fileInfo.fileName().toStdString().data());
////    QMessageBox::information(this, "Message size", "file size: " + QString::number(fileHeader.getFileSize()));
//    out.writeRawData((char*)&mainHeader, sizeof(MainHeader));
//    out.writeRawData((char*)&fileHeader, sizeof(FileHeader));
//    out.writeRawData(fileData.data(), fileData.size());
//    file.close();
//    filePath = "/home/nforce/Desktop/Dzheremi.zip";
//    QFile file2(filePath);
//    QFileInfo fileInfo2(filePath);
//    if(!file2.open(QIODevice::ReadOnly))
//        QMessageBox::critical(this, "Error", "File does not open!");
//    fileData = file2.readAll();

//    fileHeader.setData(unsigned(fileInfo2.size()), (char*)fileInfo2.fileName().toStdString().data());
//    out.writeRawData((char*)&fileHeader, sizeof(FileHeader));
//    out.writeRawData(fileData.data(), fileData.size());
//    QMessageBox::information(this, "Message size", QString::number(fileHeader.getFileSize()) + " " +
//                             fileHeader.getFileName());
//    dat = m_pTcpSocket->write(arrBlock);
//    file2.close();














//    QMessageBox::information(this, "Message size", QString::number(arrBlock.size()));

//    QFile file2("/home/nforce/Desktop/send2.cpp");
//    if(!file2.open(QIODevice::WriteOnly))
//        QMessageBox::critical(this, "Error", "File does not open!");
//    file2.write(fileData.data(), fileData.size());
//    file2.close();

//    QString message;
//    for (int i = 0; i < 50; i++)
//    {
//        message += QString::number((int)(arrBlock.data())[i]) + " ";
//        if ((i + 1) % 4 == 0)
//            message += "| ";
//    }

//    QMessageBox::critical(this, "Error", message);
//    QFile file("/home/nforce/Desktop/screen.png");
//    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        QMessageBox::critical(this, "Error", "File does not open!");
//    QByteArray fileData;
//    fileData = file.readAll();


////    m_ptxtInfo->append("Sended bytes: " + QString::number(fileData.size()));
//    file.close();
//    //out << int(273) << int(48) << int(8);

//    //out.device()->seek(0);
//    //out << quint16(arrBlock.size() - sizeof(quint16));
//    char *a;

//    QByteArray  arrBlock;
//    QDataStream out(&arrBlock, QIODevice::ReadWrite);
//    out.setVersion(QDataStream::Qt_4_5);
//    out.setByteOrder(QDataStream::LittleEndian);
//    MainHeader mainHeader;
//    mainHeader.count = 117;
//    mainHeader.msgSize = 10;
//    mainHeader.requestType = SEND_FILES;
//    out << (char*)&mainHeader << int(10);
//    QMessageBox::information(this, "Message size", QString::number(arrBlock.size()));
////    out.device()->seek(0);
//////    out << uint(arrBlock.size());


//    a = arrBlock.data();
//    QString message;
//    for (int i = 0; i < 31; i++)
//    {
//        message += QString::number((int)a[i]) + " ";
//        if ((i + 1) % 4 == 0)
//            message += "| ";
//    }

//    int dat = m_pTcpSocket->write(arrBlock);
//    m_ptxtInput->setText(message);

//    QMessageBox::information(this, "Message size", QString::number(sizeof(dat))
//                             + "  " + QString::number(arrBlock.size())
//                             + "  " + QString::number(sizeof((char*)&mainHeader)));

//    char *newData;
//    newData = arrBlock.data();


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


