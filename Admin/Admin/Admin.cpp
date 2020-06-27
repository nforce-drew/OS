#include "Admin.h"
#include "ui_Admin.h"
#include "TaskHeader.h"

Admin::Admin(const QString& strHost, int nPort, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Images/Images/gears.png"));
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

    connect(this, SIGNAL(reconnect()), this, SLOT(slotReconnect()));

    // Расположение окна по центру при запуске
    QDesktopWidget *pDescwidget = QApplication::desktop();
    move(pDescwidget->width() / 2 - width() / 2, pDescwidget->height() / 2 - height() / 2);

    // Настройка таблицы
    ui->tableTasks->setColumnCount(4);
    ui->tableTasks->setShowGrid(true);
    QStringList headerLst;
    headerLst << "ID задачи" << "Имя пользователя" << "Время" << "Статус";
    ui->tableTasks->setHorizontalHeaderLabels(headerLst);
    ui->tableTasks->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableTasks->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableTasks->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableTasks->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableTasks->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tableTasks->horizontalHeader()->setStretchLastSection(true);
    ui->tableTasks->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableTasks->verticalHeader()->setSectionsMovable(true);
    ui->tableTasks->hideColumn(0);
    ui->tableTasks->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->deleteBtn->setEnabled(false);
    connect(ui->tableTasks, SIGNAL(currentCellChanged(int, int, int, int)),
            this, SLOT(setEnabledDeleteBtn(int, int, int, int)));
    connect(ui->deleteBtn, SIGNAL(clicked()), this, SLOT(deleteTask()));
    connect(ui->tableTasks, SIGNAL(queueChanged(QList<TaskHeader>*)),
            this, SLOT(slotSendQueue(QList<TaskHeader>*)));

    QList<TaskHeader> queueList;
    setTable(queueList);

    //User Info: делаем кнопки неактивными
    ui->deleteUserBtn->setEnabled(false);
    ui->addBtn->setEnabled(false);
    ui->changeBtn->setEnabled(false);

    //Users info Настройка таблицы
    ui->usersInfoTable->setColumnCount(2);
    ui->usersInfoTable->setShowGrid(true);
    QStringList userInfoHeaderLst;
    userInfoHeaderLst << "Имя пользователя" << " Пароль" ;
    ui->usersInfoTable->setHorizontalHeaderLabels(userInfoHeaderLst);
    ui->usersInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers); //запрещено редактирование
    ui->usersInfoTable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);// растягиваем 1 столбец по содержимому
    ui->usersInfoTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);//  растягиваем 2 столбец по содержимому
    ui->usersInfoTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->usersInfoTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    //Users info
    QObject::connect(ui->usersInfoTable, SIGNAL(itemPressed(QTableWidgetItem*)),
                     this, SLOT(deleteUserBtnEnabled()));//активировать кнопку удалить
    QObject::connect(ui->deleteUserBtn, SIGNAL(clicked()),
                     this, SLOT(deleteUserBtnClicked()));
    QObject::connect(ui->deleteUserBtn,SIGNAL(clicked()),this,SLOT(deleteUser()));// удаление пользователя
    QObject::connect(ui->editPassword,SIGNAL( textChanged(const QString&)),this,SLOT(activAddBtn(const QString &)));// активировать кнопку добавить
    QObject::connect(ui->addBtn,SIGNAL(clicked()),this,SLOT(addUser()));// добавление пользователя
    QObject::connect(ui->editNewPassword,SIGNAL( textChanged(const QString&)),this,SLOT(activChangeBtn(const QString &)));//активировать кнопку изменить
    QObject::connect(ui->changeBtn,SIGNAL(clicked()),this,SLOT(changePassword()));// изменить пароль пользователя

    ui->tab_queue->setLayout(ui->layout_queue);
    ui->tab_userInfo->setLayout(ui->layout_userInfo);
    centralWidget()->setLayout(ui->layout_main);
}

void Admin::setTable(QList<TaskHeader> queueList)
{
    ui->tableTasks->setRowCount(0);
    for (int i = 0; i < queueList.size(); i++)
    {
        qDebug() << queueList[i].getUserName();
        ui->tableTasks->insertRow(i);
        ui->tableTasks->setItem(i, 0, new QTableWidgetItem(QString::number(queueList[i].getTaskId())));
        ui->tableTasks->setItem(i, 1, new QTableWidgetItem(queueList[i].getUserName()));
        ui->tableTasks->setItem(i, 2, new QTableWidgetItem(queueList[i].getTime()));
        if (i == 0)
            ui->tableTasks->setItem(i, 3, new QTableWidgetItem("Решается"));
        else
            ui->tableTasks->setItem(i, 3, new QTableWidgetItem("В очереди"));
    }
}

void Admin::deleteTask()
{
    unsigned taskId;
    int curRow;

    curRow = ui->tableTasks->currentRow();
    taskId = (unsigned)ui->tableTasks->item(curRow, 0)->text().toInt();
    ui->tableTasks->removeRow(curRow);
    ui->tableTasks->queueChanged();
    slotSendMainHdrToServer(CANCEL_TASK, taskId);
}

void Admin::slotSendMainHdrToServer(TYPE dataType, unsigned num)
{
    MainHeader mainHdr;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::ReadWrite);

    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);
    mainHdr.setData(sizeof(MainHeader), num, dataType);
    out.writeRawData((char*)&mainHdr, sizeof(MainHeader));
    m_pTcpSocket->write(arrBlock);
}

void Admin::setEnabledDeleteBtn(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if (currentRow != 0)
        ui->deleteBtn->setEnabled(true);
}

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


void Admin::slotSendQueue(QList<TaskHeader>* queueLst)
{
    MainHeader  mainHdr;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::ReadWrite);
    unsigned    dataSize;

    dataSize = queueLst->size() * sizeof(TaskHeader);
    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);
    qDebug() << "=== Queue sended ===";
    mainHdr.setData(sizeof(MainHeader) + dataSize, queueLst->size(), QUEUE_LIST);
    out.writeRawData((char*)&mainHdr, sizeof(MainHeader));
    for (TaskHeader task : *queueLst)
    {
        out.writeRawData((char*)&task, sizeof(TaskHeader));
    }
    m_pTcpSocket->write(arrBlock);
}

void Admin::slotReconnect()
{
//    qDebug() << "reconnect";
    m_pTcpSocket->connectToHost(m_strHost, m_nPort);
}

void Admin::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    QByteArray  data;
    MainHeader  mainHeader;

    qDebug() << "Receiving data..." << m_pTcpSocket->bytesAvailable();
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
    if (mainHeader.getType() == QUEUE_LIST)
    {
        data.clear();
        data.reserve(mainHeader.getMsgSize() - sizeof(MainHeader));
        qDebug() << mainHeader.getMsgSize() << " " << mainHeader.getCount() << " " << mainHeader.getType();
//        qDebug() << in.readRawData(data.data(), mainHeader.getMsgSize() - sizeof(MainHeader));
        QList<TaskHeader> queueList;
        TaskHeader taskHdr;
        for (int i = 0; i < (int)mainHeader.getCount(); i++)
        {
            in.readRawData((char*)&taskHdr, sizeof(taskHdr));
            queueList << taskHdr;
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
        for (int i = 0; i < (int)mainHeader.getCount(); i++)
        {
            in.readRawData(user, 20);
            onlineLst.push_back(user);
        }
        setOnlineUsers(onlineLst);
    }
    if (mainHeader.getType() == USERS_INFO)
    {
        QList<QVector<QString>> usersInfoList;
        QVector<QString>        userInfo;
        LoginHeader             loginHdr;
        char                    data[sizeof(LoginHeader)];
        qDebug() << "MAIN HEADER msgSize: " << mainHeader.getMsgSize() <<
                    " count: " << mainHeader.getCount() <<
                    " type: " << mainHeader.getType();
        qDebug() << m_pTcpSocket->bytesAvailable();
        for (int i = 0; i < (int)mainHeader.getCount(); i++)
        {
            in.readRawData(data, sizeof(LoginHeader));
            loginHdr.setByteArr(data);
            qDebug() << "LOGIN HEADER user name: " << loginHdr.getUserName() <<
                        " password " << loginHdr.getUserPassword();
            userInfo.clear();
            userInfo.push_back(QString(loginHdr.getUserName()));
            userInfo.push_back(QString(loginHdr.getUserPassword()));
            usersInfoList.push_back(userInfo);
        }
        fillUserInfoTable(usersInfoList);
        fillUserNamesCmbBox(usersInfoList);
    }
    qDebug() << "End of data reading.";
}

void Admin::slotError(QAbstractSocket::SocketError err)
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
//        QMessageBox::critical(this, "Ошибка", strError);
//        m_pTcpSocket->abort();
        m_pTcpSocket->close();
        QTimer::singleShot(0, this, SLOT(slotReconnect()));
//        QTimer::singleShot(0, m_pTcpSocket, SLOT(connectToHost()));
//    }
//    qDebug() << "m_lastStatus = " << m_lastStatus;
//    m_lastStatus = false;
//    emit reconnect();
//    QMetaObject::invokeMethod(m_pTcpSocket, "connectToHost", Qt::QueuedConnection);
//    m_pTcpSocket->reset();

}

void Admin::slotConnected()
{
    m_lastStatus = true;
    slotSendDataToServer(ADMIN_LOGGED, 0, NULL, 0);
    ui->statusBar->setText("Подключен к серверу");
}

// ------------------------------------------------------------------
void Admin::slotSendDataToServer(TYPE dataType, unsigned count, char* data, unsigned len)
{
    MainHeader mainHdr;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::ReadWrite);

    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);
    mainHdr.setData(sizeof(MainHeader) + len, count, dataType);
    out.writeRawData((char*)&mainHdr, sizeof(MainHeader));
    if (data != NULL && len != 0)
        out.writeRawData(data, len);
    m_pTcpSocket->write(arrBlock);
    qDebug() << "SENDED: " << bytes(arrBlock.data(), 30);
}
// ------------------------------------------------------------------
void Admin::deleteUserBtnClicked()
{
    int row;
    char userName[20];

    row = ui->usersInfoTable->currentRow();
    strcpy(userName, ui->usersInfoTable->item(row, 0)->text().toStdString().c_str());
    slotSendDataToServer(DELETE_USER, 0, userName, 20);
    ui->comboBox->removeItem(row + 1);
    QMessageBox::information(this,"Информация","Пользователь " + QString(userName) + " успешно удален!");
    ui->usersInfoTable->removeRow(row);
    ui->deleteBtn->setEnabled(false);
}
// ------------------------------------------------------------------
void Admin::deleteUserBtnEnabled()
{
    ui->deleteUserBtn->setEnabled(true);
}
// ------------------------------------------------------------------
void Admin::setOnlineUsers(QStringList users)
{
    ui->listUsers->clear();
    ui->listUsers->addItems(users);
}
// ------------------------------------------------------------------
void Admin::fillUserInfoTable(QList<QVector<QString>> list)
{
    int rowCount = ui->usersInfoTable->rowCount();
    //заполнение таблицы
    for (int i = 0; i < rowCount; i++)
    {
        ui->usersInfoTable->removeRow(i);
    qDebug() << i;
    }
    for (int i = 0; i < list.size(); ++i)
    {
        ui->usersInfoTable->insertRow(i);
        QTableWidgetItem *username = new QTableWidgetItem;
        QTableWidgetItem *pass = new QTableWidgetItem;
        username->setText(list[i][0]);
        pass->setText(list[i][1]);
        ui->usersInfoTable->setItem(i,0,username);
        ui->usersInfoTable->setItem(i,1,pass);
    }
}
// ------------------------------------------------------------------
void Admin::fillUserNamesCmbBox(QList<QVector<QString>> list)
{
    for(int i = 0; i < list.size(); ++i)
        ui->comboBox->addItem(list[i].at(0));
}
// ------------------------------------------------------------------
Admin::~Admin()
{
    delete ui;
}
// ------------------------------------------------------------------
