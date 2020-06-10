#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>
#include <QTableWidget>
#include <QDropEvent>
#include <QTableView>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Admin; }
QT_END_NAMESPACE

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    Admin(QWidget *parent = nullptr);
    ~Admin();

 public slots:
    void btn (QTableWidgetItem  *itm);
    void deleteTask();
    void movedTask( int logicIndex , int oldVisualIndex , int newVisualIndex );

private:
    Ui::Admin *ui;

};
#endif // ADMIN_H
