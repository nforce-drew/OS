#include "Admin.h"
#include "ui_Admin.h"
#include "QueueHeader.h"

Admin::Admin(const QString& strHost, int nPort, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    // Настройка клиент-серверной части
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

    // Расположение окна по центру при запуске
    QDesktopWidget *pDescwidget=QApplication::desktop();
    move(pDescwidget->width()/2-width()/2, pDescwidget->height()/2-height()/2);

    // Настройка таблицы
    ui->tableTasks->setColumnCount(3);
    ui->tableTasks->setShowGrid(true);
    QStringList headerLst;
    headerLst << "Имя пользователя" << "Время" << "Статус";
    ui->tableTasks->setHorizontalHeaderLabels(headerLst);
    ui->tableTasks->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableTasks->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableTasks->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableTasks->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableTasks->horizontalHeader()->setStretchLastSection(true);
    ui->tableTasks->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableTasks->verticalHeader()->setSectionsMovable(true);
    ui->tableTasks->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->deleteBtn->setEnabled(false);
    connect(ui->tableTasks, SIGNAL(currentCellChanged(int, int, int, int)),
            this, SLOT(setEnabledDeleteBtn()));
    connect(ui->deleteBtn, SIGNAL(clicked()), this, SLOT(deleteTask()));
//    ui->tableTasks->curr

    QList<QueueHeader> queueList;
    setTable(queueList);
    ui->tableTasks->queueChanged();

    centralWidget()->setLayout(ui->main_Layout);
}

void Admin::setTable(QList<QueueHeader> queueList)
{
    ui->tableTasks->setRowCount(0);

//    for (int i = 0; i < 10; i++)
//    {
//        queueHdr.setData((char*)QString("User " + QString::number(i)).toStdString().c_str() , i + 1, "11:22:11");
//        queueList << queueHdr;
//    }
    for (int i = 0; i < queueList.size(); i++)
    {
        qDebug() << queueList[i].getUserName();
        ui->tableTasks->insertRow(i);
        ui->tableTasks->setItem(i, 0, new QTableWidgetItem(queueList[i].getUserName()));
        ui->tableTasks->setItem(i, 1, new QTableWidgetItem(queueList[i].getTime()));
        if (i == 0)
            ui->tableTasks->setItem(i, 2, new QTableWidgetItem("Решается"));
        else
            ui->tableTasks->setItem(i, 2, new QTableWidgetItem("В очереди"));
    }
}

void Admin::deleteTask()
{
    ui->tableTasks->removeRow(ui->tableTasks->currentRow());
    ui->tableTasks->queueChanged();
}

void Admin::setEnabledDeleteBtn()
{
    ui->deleteBtn->setEnabled(true);
}

void Admin::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    QByteArray  data;
    MainHeader  mainHeader;

    qDebug() << "Receiving data..." << m_pTcpSocket->bytesAvailable();
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
    if (mainHeader.getType() == QUEUE_LIST)
    {
        data.clear();
        data.reserve(mainHeader.getMsgSize() - sizeof(MainHeader));
        qDebug() << mainHeader.getMsgSize() << " " << mainHeader.getCount() << " " << mainHeader.getType();
//        qDebug() << in.readRawData(data.data(), mainHeader.getMsgSize() - sizeof(MainHeader));
        QList<QueueHeader> queueList;
        QueueHeader queueHdr;
        for (int i = 0; i < mainHeader.getCount(); i++)
        {
            in.readRawData((char*)&queueHdr, sizeof(queueHdr));
            queueList << queueHdr;
        }
        setTable(queueList);
    }
    if (mainHeader.getType() == ONLINE_USERS)
    {
        QStringList onlineLst;
        char        user[20];

        data.clear();
        data.reserve(mainHeader.getMsgSize() - sizeof(MainHeader));
        qDebug() << mainHeader.getMsgSize() << " " << mainHeader.getCount() << " " << mainHeader.getType();
        for (int i = 0; i < mainHeader.getCount(); i++)
        {
            in.readRawData(user, 20);
            onlineLst.push_back(user);
        }
        setOnlineUsers(onlineLst);
    }
    qDebug() << "End of data reading.";
}

void Admin::slotError(QAbstractSocket::SocketError err)
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
        ui->statusBar->setText(strError);
        QMessageBox::critical(this, "Ошибка", strError);
        m_pTcpSocket->close();
    }
    m_lastStatus = false;
    m_pTcpSocket->connectToHost(m_strHost, m_nPort);
}

void Admin::slotConnected()
{
    m_lastStatus = true;
    slotSendDataToServer(ADMIN_LOGGED, NULL, 0);
    ui->statusBar->setText("Подключен к серверу");
}

// ------------------------------------------------------------------
void Admin::slotSendDataToServer(TYPE dataType, char* data, unsigned len)
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

void Admin::setOnlineUsers(QStringList users)
{
    ui->listUsers->clear();
    ui->listUsers->addItems(users);
}

Admin::~Admin()
{
    delete ui;
}
