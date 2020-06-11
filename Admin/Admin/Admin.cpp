#include "Admin.h"
#include "ui_Admin.h"
#include "QueueHeader.h"

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    // Настройка таблицы
    ui->tableTasks->setColumnCount(2);
    ui->tableTasks->setShowGrid(true);
    QStringList headerLst;
    headerLst << "Имя пользователя" << "Время";
    ui->tableTasks->setHorizontalHeaderLabels(headerLst);
    ui->tableTasks->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableTasks->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableTasks->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
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
    QueueHeader queueHdr;

    for (int i = -1; i < 10; i++)
    {
        queueHdr.setData((char*)QString("User " + QString::number(i)).toStdString().c_str() , i + 1, "11:22:11");
        queueList << queueHdr;
    }
    for (int i = 1; i < queueList.size(); i++)
    {
        qDebug() << queueList[i].getUserName();
        ui->tableTasks->insertRow(i - 1);
        ui->tableTasks->setItem(i - 1, 0, new QTableWidgetItem(queueList[i].getUserName()));
        ui->tableTasks->setItem(i - 1, 1, new QTableWidgetItem(queueList[i].getTime()));
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

void Admin::setOnlineUsers(QStringList users)
{
    ui->listUsers->addItems(users);
}

Admin::~Admin()
{
    delete ui;
}
