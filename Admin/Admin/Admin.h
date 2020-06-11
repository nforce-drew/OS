#ifndef ADMIN_H
#define ADMIN_H

#include "QueueHeader.h"
#include "QueueTable.h"
#include <QMainWindow>
#include <QList>
#include <QDebug>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = 0);
    ~Admin();

private:
    Ui::Admin *ui;

private:
    void    setTable(QList<QueueHeader> queueList);

public slots:
    void    slotQueueChanged();
};

#endif // ADMIN_H
