#ifndef ADVANCEDTABLEW_H
#define ADVANCEDTABLEW_H

#include <QObject>
#include <QtWidgets>

class AdvancedTableW : public QTableWidget
{
    Q_OBJECT
public:
    AdvancedTableW(QWidget * parent = 0);
private:
    void mousePressEvent(QMouseEvent * event);
    //void mouseMoveEvent(QMouseEvent * event);
    //void keyPressEvent(QKeyEvent *event);
    void dropEvent(QDropEvent * event);
};
#endif // ADVANCEDTABLEW_H
