#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Admin)
{
    ui->setupUi(this);

    ui->tableTasks->verticalHeader()->setSectionsMovable(true);
    ui->deleteBtn->setEnabled(false);

//    ui->tableTasks->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->tableTasks->setDragEnabled(true);
//    ui->tableTasks->setAcceptDrops(true);
//    ui->tableTasks->viewport()->setAcceptDrops(true);
//     ui->tableTasks->setDropIndicatorShown(true);
//    ui->tableTasks->setDragDropMode(QAbstractItemView::InternalMove);
//    ui->tableTasks->setDragDropOverwriteMode(false);
//    ui->tableTasks->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableTasks->horizontalHeader()->resizeSection(0,210);
    ui->tableTasks->horizontalHeader()->resizeSection(1,160);
    ui->tableTasks->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);

    QObject::connect(ui->tableTasks,SIGNAL(itemPressed(QTableWidgetItem  *)),this,SLOT(btn(QTableWidgetItem  *)));
    QObject::connect(ui->deleteBtn,SIGNAL(clicked()),this,SLOT(deleteTask()));
    QObject::connect(ui->tableTasks->verticalHeader(),SIGNAL(sectionMoved (int,int,int )),this,SLOT(movedTask(int,int,int)));

}


void Admin::btn(QTableWidgetItem *)
{
  ui->deleteBtn->setEnabled(true);
}

void Admin::deleteTask()
{
    ui->tableTasks->removeRow(ui->tableTasks->currentRow());
}

void Admin::movedTask(int , int , int)
{

}

Admin::~Admin()
{
    delete ui;
}

