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
    ui->newPassBtn->setEnabled(false);
    ui->editNewPassword->setEnabled(false);

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

    ui->errorAddUser_label->setStyleSheet("color: red");


    //Users info
    QObject::connect(ui->usersInfoTable, SIGNAL(itemPressed(QTableWidgetItem*)),
                     this, SLOT(deleteUserBtnEnabled()));//активировать кнопку удалить
    QObject::connect(ui->deleteUserBtn, SIGNAL(clicked()),
                     this, SLOT(deleteUserBtnClicked()));// удаление пользователя
    QObject::connect(ui->editPassword, SIGNAL(textChanged(const QString&)), this, SLOT(editPasswordChanged(const QString&)));// активировать кнопку добавить
    QObject::connect(ui->editUsername, SIGNAL(textChanged(const QString&)), this, SLOT(editLoginChanged(const QString&)));// активировать кнопку добавить
    QObject::connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(addBtnClicked()));// добавление пользователя
    QObject::connect(ui->editNewPassword, SIGNAL(textChanged(const QString&)), this, SLOT(editNewPasswordChanged(const QString &)));//активировать кнопку изменить
    QObject::connect(ui->newPassBtn, SIGNAL(clicked()), this, SLOT(newPassBtnClicked()));// изменить пароль пользователя
    QObject::connect(ui->comboBox, SIGNAL(currentTextChanged(const QString&)),
                     this, SLOT(comboBoxChanged(const QString&)));

    QObject::connect(ui->addBinBtn, SIGNAL(clicked()), this, SLOT(addBinBtnClicked()));


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

    ui->deleteBtn->setEnabled(false);
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
    mainHdr.setData(sizeof(MainHeader), num, dataType, 0);
    out.writeRawData((char*)&mainHdr, sizeof(MainHeader));
    m_pTcpSocket->write(arrBlock);
}

void Admin::slotSendBinToServer()
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

    qDebug() << "slotSendBinToServer()";

    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);
    fPaths.push_back(m_newBin);
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
    mainHeader.setData(msgSize, fPaths.size(), SEND_BIN, 0);
    arrBlock.clear();
    out.device()->seek(0);
    out.writeRawData((char*)&mainHeader, sizeof(MainHeader));
    totalSent += m_pTcpSocket->write(arrBlock);
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
        totalSent += m_pTcpSocket->write(arrBlock);
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
                totalSent += m_pTcpSocket->write(arrBlock);
                qDebug() << "sent =" << totalSent;
            }
//            j++;
        }
        p_file->close();
        delete p_file;
    }
    qDebug() << "BYTES sent: " << totalSent;
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
    mainHdr.setData(sizeof(MainHeader) + dataSize, queueLst->size(), QUEUE_LIST, 0);
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
    if (mainHeader.getType() == BINS_LIST)
    {
        FileHeader  fileHdr;
        QStringList binsNames;

        qDebug() << "BINS_LIST " << mainHeader.getMsgSize();
        for (int i = 0; i < (int)mainHeader.getCount(); i++)
        {
            in.readRawData((char*)&fileHdr, sizeof(FileHeader));
            binsNames.push_back(QString(fileHdr.getFileName()).section('/', -1));
        }
        fillBinsList(binsNames);
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
    mainHdr.setData(sizeof(MainHeader) + len, count, dataType, 0);
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
void Admin::editPasswordChanged(const QString &text)
{
    if (text.size() > 19)
    {
        ui->addBtn->setEnabled(false);
        ui->errorAddUser_label->setText("Длина пароля превышает\n19 символов!");
        return;
    }
    else if (ui->editUsername->text().size() > 19)
    {
        ui->addBtn->setEnabled(false);
        ui->errorAddUser_label->setText("Длина имени превышает\n19 символов!");
        return;
    }
    else
        ui->errorAddUser_label->setText("");
    for (auto userInfo : m_usersInfo)
        if (userInfo[0] == ui->editUsername->text())
        {
            ui->addBtn->setEnabled(false);
            ui->errorAddUser_label->setText("Имя " + ui->editUsername->text()
                                            + " уже существует!");
            return;
        }
    if (!text.isEmpty() && !ui->editUsername->text().isEmpty())
        ui->addBtn->setEnabled(true);
    if (text.isEmpty())
        ui->addBtn->setEnabled(false);
}
// ------------------------------------------------------------------
void Admin::editLoginChanged(const QString &text)
{
    if (text.size() > 19)
    {
        ui->addBtn->setEnabled(false);
        ui->errorAddUser_label->setText("Длина имени превышает\n19 символов!");
        return;
    }
    else if (ui->editPassword->text().size() > 19)
    {
        ui->addBtn->setEnabled(false);
        ui->errorAddUser_label->setText("Длина пароля превышает\n19 символов!");
        return;
    }
    else
        ui->errorAddUser_label->setText("");
    for (auto userInfo : m_usersInfo)
        if (userInfo[0] == text)
        {
            ui->addBtn->setEnabled(false);
            ui->errorAddUser_label->setText("Имя " + text + " уже существует!");
            return;
        }
    if (!text.isEmpty() && !ui->editPassword->text().isEmpty())
        ui->addBtn->setEnabled(true);
    if (text.isEmpty())
        ui->addBtn->setEnabled(false);
}

void Admin::addBtnClicked()
{
    LoginHeader loginHdr;
    char        userName[20];
    char        password[20];

    strcpy(userName, ui->editUsername->text().toStdString().c_str());
    strcpy(password, ui->editPassword->text().toStdString().c_str());
    ui->editUsername->setText("");
    ui->editPassword->setText("");
    ui->addBtn->setEnabled(false);
    loginHdr.setData(userName, password);
    slotSendDataToServer(ADD_NEW_USER, 1, (char*)&loginHdr, sizeof(LoginHeader));
}

void Admin::editNewPasswordChanged(const QString &text)
{
    if (text.size() > 19)
    {
        ui->newPassBtn->setEnabled(false);
        ui->errorNewPass_label->setText("Длина пароля превышает\n19 символов!");
        return;
    }
    else
        ui->errorNewPass_label->setText("");
    if (text.isEmpty())
    {
        ui->newPassBtn->setEnabled(false);
        return;
    }
    ui->newPassBtn->setEnabled(true);
}

void Admin::comboBoxChanged(const QString &text)
{
    if (text == "-Выберите пользователя-")
    {
        ui->editNewPassword->setEnabled(false);
        ui->editNewPassword->clear();
    }
    else
        ui->editNewPassword->setEnabled(true);
}
// ------------------------------------------------------------------
void Admin::newPassBtnClicked()
{
    LoginHeader loginHdr;
    char        userName[20];
    char        password[20];

    strcpy(userName, ui->comboBox->currentText().toStdString().c_str());
    strcpy(password, ui->editNewPassword->text().toStdString().c_str());
    ui->comboBox->setCurrentIndex(0);
    ui->editNewPassword->setText("");
    ui->newPassBtn->setEnabled(false);
    loginHdr.setData(userName, password);
    slotSendDataToServer(CHANGE_PASSWORD, 1, (char*)&loginHdr, sizeof(LoginHeader));
}
// ------------------------------------------------------------------
void Admin::addBinBtnClicked()
{
    m_newBin = QFileDialog::getOpenFileName(this, "Выбор бинарника", "");
    if (!m_newBin.isEmpty())
        slotSendBinToServer();
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
    m_usersInfo = list;
    ui->deleteUserBtn->setEnabled(false);
    int rowCount = ui->usersInfoTable->rowCount();
    for (int i = 0; i < rowCount; i++)
        ui->usersInfoTable->removeRow(0);
    //заполнение таблицы
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
    ui->comboBox->clear();
    ui->comboBox->addItem("-Выберите пользователя-");
    for(int i = 0; i < list.size(); ++i)
        ui->comboBox->addItem(list[i][0]);
}
// ------------------------------------------------------------------
void Admin::fillBinsList(QStringList binsNames)
{
    ui->binList->clear();
    ui->binList->addItems(binsNames);

}
// ------------------------------------------------------------------
Admin::~Admin()
{
    delete ui;
}
// ------------------------------------------------------------------
