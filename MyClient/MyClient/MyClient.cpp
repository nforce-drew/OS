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
    ui(new Ui::MyClient)
{
//    setWindowIcon(QIcon(":/Images/Images/user.png"));
    ui->setupUi(this);
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

    connect(ui->dropArea, SIGNAL(dropped(QStringList)), this, SLOT(slotDroppedFiles(QStringList)));



    m_ptxtInfo  = new QTextEdit;
    m_ptxtInput = new QLineEdit;

//    connect(m_ptxtInput, SIGNAL(returnPressed()),
//            this,        SLOT(slotSendFilesToServer())
//           );

    connect(ui->solveBtn, SIGNAL(clicked()), SLOT(slotSolveClicked()));
    ui->solveBtn->setEnabled(false);

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
    m_loginWndw = new LogInWindow(this);

    if (((LogInWindow*)m_loginWndw)->exec() == QDialog::Accepted)
    {
        qDebug() << "User " + ((LogInWindow*)m_loginWndw)->getUserName() + " logged.";
//        show();
        QMessageBox::information(this, "Logged", "User " + ((LogInWindow*)m_loginWndw)->getUserName() + " logged.");
    }
    m_userName = ((LogInWindow*)m_loginWndw)->getUserName();
    qDebug() << "logged: " << m_userName;
    setWindowIcon(QIcon(":/Images/Images/user.png"));
//    m_loginWndw->show();
    setLayout(ui->verticalLayout);

}

void MyClient::setTasksList(QList<TaskStateHeader> &tasksList)
{
    m_tasksList.clear();
    ui->tasksList->clear();
    QPixmap *pixOK = new QPixmap(":/Images/Images/done.png");
    QPixmap *pixCancel = new QPixmap(":/Images/Images/cancel.png");
    QPixmap *pixLoading = new QPixmap(":/Images/Images/solving.png");
    QPixmap* pixInQueue = new QPixmap(":/Images/Images/in_queue.png");
    bool solving = false;

    for (int i = 0; i < tasksList.size(); ++i)
    {
        if (tasksList[i].getState() == DONE) //если состояние готово,ставим галочку
        {
            QLayout* layoutOK = new QHBoxLayout;
            QLabel *pixLblOK = new QLabel();
            pixLblOK->setPixmap(*pixOK);
            QWidget* wgt = new QWidget;
            layoutOK->addWidget(pixLblOK);
            QLabel *text = new QLabel();
            text->setText(tasksList[i].getTime());
            layoutOK->addWidget(text);
            QPushButton* btnDownLoad = new QPushButton("Download");
            btnDownLoad->setObjectName(QString::number(ui->tasksList->count() - 1));
            connect( btnDownLoad, SIGNAL( clicked() ), SLOT( slotDownloadClicked() ) );
            layoutOK->addWidget(btnDownLoad);
            wgt->setLayout(layoutOK);
            QListWidgetItem* item = new QListWidgetItem(ui->tasksList);
            wgt->setObjectName(QString::number(tasksList[i].getTaskId()));
            item->setSizeHint(wgt->sizeHint());
            ui->tasksList->setItemWidget(item, wgt);
        }
        if (tasksList[i].getState() == CANCEL)//если состояние "отменено",ставим крестик
        {
            QLayout* layoutCancel = new QHBoxLayout;
            QLabel *pixLblCancel = new QLabel();
            pixLblCancel->setPixmap(*pixCancel);
            QWidget* wgt = new QWidget;
            layoutCancel->addWidget(pixLblCancel);
            QLabel *text = new QLabel();
            text->setText(tasksList[i].getTime());
            layoutCancel->addWidget(text);
            QLabel *text2 = new QLabel();
            text2->setText("Canceled");
            layoutCancel->addWidget(text2);
            wgt->setLayout( layoutCancel );
            QListWidgetItem* item = new QListWidgetItem( ui->tasksList );
            wgt->setObjectName(QString::number(tasksList[i].getTaskId()));
            item->setSizeHint( wgt->sizeHint() );
            ui->tasksList->setItemWidget( item, wgt );
        }
        if (tasksList[i].getState() == SOLVING)//если состояние "в очереди",ставим часы
        {
            QLayout* layoutLoading = new QHBoxLayout;
            QLabel *pixLblLoading = new QLabel();
            pixLblLoading->setPixmap(*pixLoading);
            QWidget* wgt = new QWidget;
            layoutLoading->addWidget(pixLblLoading);
            QLabel *text = new QLabel();
            text->setText(tasksList[i].getTime());
            layoutLoading->addWidget(text);
            wgt->setLayout( layoutLoading );
            QListWidgetItem* item = new QListWidgetItem( ui->tasksList );
            wgt->setObjectName(QString::number(tasksList[i].getTaskId()));
            item->setSizeHint( wgt->sizeHint() );
            ui->tasksList->setItemWidget( item, wgt );
            solving = true;
        }
        if (tasksList[i].getState() == IN_QUEUE)//если состояние "в очереди",ставим часы
        {
            QLayout* layoutInQueue = new QHBoxLayout;
            QLabel *pixLblInQueue = new QLabel();
            pixLblInQueue->setPixmap(*pixInQueue);
            QWidget* wgt = new QWidget;
            layoutInQueue->addWidget(pixLblInQueue);
            QLabel *text = new QLabel();
            text->setText(tasksList[i].getTime());
            layoutInQueue->addWidget(text);
            wgt->setLayout( layoutInQueue );
            QListWidgetItem* item = new QListWidgetItem( ui->tasksList );
            QPushButton* btnCancel = new QPushButton("Отменить");
            btnCancel->setObjectName(QString::number(ui->tasksList->count() - 1));
            connect( btnCancel, SIGNAL( clicked() ), SLOT( slotCancelClicked() ) );
            layoutInQueue->addWidget( btnCancel );
            wgt->setObjectName(QString::number(tasksList[i].getTaskId()));
            item->setSizeHint( wgt->sizeHint() );
            ui->tasksList->setItemWidget( item, wgt );
        }
        m_tasksList.push_back(tasksList[i]);
    }
    if (!solving && ui->filesList->count() != 0)
    {
        ui->solveBtn->setEnabled(true);
//        m_tasksList.clear();
//        ui->dropArea->clearFiles();
    }
}

void MyClient::successRecieve()
{
    ui->dropArea->clearFiles();
}

void MyClient::slotCancelClicked()
{
    qDebug() << "slotCancelClicked()";
    QPushButton* pBtn = qobject_cast<QPushButton*>(sender());
    pBtn->setText("Сменил");
    int row = pBtn->objectName().toInt();
    QListWidgetItem *itm = ui->tasksList->item(row);
    QWidget* wgt = new QWidget;
    QLayout* layoutCancel = new QHBoxLayout;
    QPixmap *pixCancel = new QPixmap(":/Images/Images/cancel.png");
    QLabel *pixLblCancel = new QLabel();
    pixLblCancel->setPixmap(*pixCancel);
    layoutCancel->addWidget(pixLblCancel);
    QLabel *text = new QLabel();
    text->setText(m_tasksList[row].getTime());
    layoutCancel->addWidget(text);
    QLabel *text2 = new QLabel();
    text2->setText("Canceled");
    layoutCancel->addWidget(text2);
    wgt->setLayout( layoutCancel );
    itm->setSizeHint( wgt->sizeHint() );
    ui->tasksList->setItemWidget( itm, wgt );
    slotSendMainHdrToServer(CANCEL_TASK, m_tasksList[row].getTaskId());
    qDebug() << m_tasksList[row].getTaskId();
}

void MyClient::slotDownloadClicked()
{
    QPushButton* pBtn = qobject_cast<QPushButton*>(sender());
    int row = pBtn->objectName().toInt();
    unsigned taskId = m_tasksList[row + 1].getTaskId();
    qDebug() << taskId;
    slotSendMainHdrToServer(GET_SOLUTION, taskId);
}

void MyClient::slotSolveClicked()
{
    ui->solveBtn->setEnabled(false);
    ui->filesList->clear();
    slotSendFilesToServer();
}

void MyClient::slotSendMainHdrToServer(TYPE dataType, unsigned num)
{
    MainHeader mainHdr;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::ReadWrite);

    qDebug() << "slotSendMainHdrToServer() " << dataType;
    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);
    mainHdr.setData(sizeof(MainHeader), num, dataType);
    out.writeRawData((char*)&mainHdr, sizeof(MainHeader));
    m_pTcpSocket->write(arrBlock);
    qDebug() << bytes(arrBlock.data(), 15);
}

// ----------------------------------------------------------------------
void MyClient::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    QByteArray  data;
    MainHeader  mainHeader;
    FileHeader  fileHeader;

    qDebug() << "Receiving data...";
    if (m_pTcpSocket->bytesAvailable() < (qint64)sizeof(MainHeader))
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
        for (int i = 0; i < (int)mainHeader.getCount(); i++)
        {
            in.readRawData((char*)&fileHeader, sizeof(FileHeader));
            qDebug() << "FileHeader: " << fileHeader.getFileSize() << " " << fileHeader.getFileName();
            data.resize(fileHeader.getFileSize());
            in.readRawData(data.data(), data.size());

            //путь для сохранения
            QFile file("/home/nspace/Desktop/ClientReceive/" + QString(fileHeader.getFileName()));
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Truncate))
            {
                qDebug() << "Error: opening the file for writing "
                            << "/home/nspace/Desktop/ClientReceive/" << fileHeader.getFileName();
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
    if (mainHeader.getType() == TASKS_INFO)
    {
        qDebug() << "TASKS_INFO";
        data.clear();
        data.reserve(mainHeader.getMsgSize() - sizeof(MainHeader));
//        qDebug() << mainHeader.getMsgSize() << " " << mainHeader.getCount() << " " << mainHeader.getType();
//        qDebug() << in.readRawData(data.data(), mainHeader.getMsgSize() - sizeof(MainHeader));
        QList<TaskStateHeader> tasksList;
        TaskStateHeader taskStateHdr;
        for (int i = 0; i < (int)mainHeader.getCount(); i++)
        {
            in.readRawData((char*)&taskStateHdr, sizeof(TaskStateHeader));
            tasksList << taskStateHdr;
//            qDebug() << taskStateHdr.getState() << " " << taskStateHdr.getTime() << " " << taskStateHdr.getTaskId();
        }
        setTasksList(tasksList);
    }
    if (mainHeader.getType() == SUCCESS_RECIEVE)
    {
        qDebug() << "SUCCESS_RECIEVE";
        successRecieve();
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
        ui->statusBar->setText(strError);
        m_pTcpSocket->close();
        QTimer::singleShot(0, this, SLOT(slotReconnect()));
}
// ----------------------------------------------------------------------
void MyClient::slotReconnect()
{
//    qDebug() << "reconnect";
    m_pTcpSocket->connectToHost(m_strHost, m_nPort);
}
// ----------------------------------------------------------------------
void MyClient::slotDroppedFiles(QStringList newFiles)
{
    qDebug() << "SLOT DROPPED";
    ui->solveBtn->setEnabled(true);
    QListWidgetItem* pItem = 0;
    qDebug() << newFiles.size();
    for (QString file : newFiles)
    {
        pItem = new QListWidgetItem(file, ui->filesList);
    }
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

    qDebug() << "slotSendFilesToServer()";

    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);
    fPaths = ui->dropArea->getFiles();
//    fPaths << "/home/nspace/Desktop/AllDesktop/Dzheremi.djvu"
//           << "/home/nspace/Desktop/AllDesktop/scrn29.png"
//           << "/home/nspace/Desktop/AllDesktop/Конспект_24.03.pdf"
//           << "/home/nspace/Desktop/AllDesktop/crock.jpg";// Удалить
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

    ui->statusBar->setText("Received the connected() signal");
}

MyClient::~MyClient()
{
    delete ui;
}


