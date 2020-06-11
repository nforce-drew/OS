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
    ui->tableTasks->verticalHeader()->setSectionsMovable(true);
    ui->tableTasks->verticalHeader()->setFixedWidth(25);

//    connect(ui->tableTasks->verticalHeader(), SIGNAL(sectionMoved(int, int, int)),
//            this, SLOT(slotQueueChanged()));
    QList<QueueHeader> queueList;
    setTable(queueList);
//    (qobject_cast<QueueTable*>(ui->tableTasks))->queueChanged();

    centralWidget()->setLayout(ui->main_Layout);
}

void Admin::setTable(QList<QueueHeader> queueList)
{
    QueueHeader queueHdr;
    qDebug() << "setTable";
    for (int i = 0; i < 10; i++)
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
//    ui->tableTasks->setSortingEnabled(Qt::AscendingOrder);
}

void    Admin::slotQueueChanged()
{
    int         rowCount;
    QStringList vertHdrList;

    rowCount =ui->tableTasks->verticalHeader()->count();
    qDebug() << "slotQueueChanged()";
    for (int i = 0; i < rowCount; i++)
        vertHdrList << QString::number(i + 2);
    ui->tableTasks->setVerticalHeaderLabels(vertHdrList);
}

Admin::~Admin()
{
    delete ui;
}
