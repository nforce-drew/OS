#ifndef DROPZONE_H
#define DROPZONE_H

#include <QtGui>
#include <QLabel>
#include <QStringList>

// ======================================================================
class DropArea : public QLabel
{
Q_OBJECT

private:
    QStringList m_files;


public:
    DropArea(QWidget* pwgt = 0);
    QStringList getFiles();
    void clearFiles();
protected:
    virtual void dragEnterEvent(QDragEnterEvent* pe);
    virtual void dropEvent(QDropEvent* pe);

signals:
    void dropped(QStringList newFiles);

};

#endif // DROPZONE_H
