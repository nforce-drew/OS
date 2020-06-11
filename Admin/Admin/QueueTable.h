#ifndef QUEUETABLE_H
#define QUEUETABLE_H

#include "Admin.h"
#include <QObject>
#include <QtWidgets>

class QueueTable : public QTableWidget
{
    Q_OBJECT
public:
    QueueTable(QWidget * parent = 0);
private:
    void mousePressEvent(QMouseEvent*   event);
    void moveEvent      (QMoveEvent*    event);
    void dropEvent      (QDropEvent*    event);
public:
    void queueChanged   ();
};

#endif // QUEUETABLE_H
