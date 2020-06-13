#ifndef QUEUETABLE_H
#define QUEUETABLE_H

#include "Admin.h"
#include "TaskHeader.h"
#include <QObject>
#include <QtWidgets>

class QueueTable : public QTableWidget
{
    Q_OBJECT
private:
    QList<TaskHeader>*  m_queueList;
public:
    QueueTable(QWidget * parent = 0);
    ~QueueTable();
private:
    void mousePressEvent(QMouseEvent*   event);
    void dropEvent      (QDropEvent*    event);
public slots:
    void queueChanged   ();
signals:
    void queueChanged   (QList<TaskHeader>* queueList);
};

#endif // QUEUETABLE_H
