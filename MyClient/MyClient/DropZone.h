#ifndef DROPZONE_H
#define DROPZONE_H

#include <QtGui>
#include <QLabel>
#include <QStringList>

// ======================================================================
class DropZone : public QLabel {
Q_OBJECT

private:
    QStringList m_files;
    QStringList m_newFiles;

protected:
    virtual void dragEnterEvent(QDragEnterEvent* pe)
    {
        if (pe->mimeData()->hasFormat("text/uri-list")) {
            pe->acceptProposedAction();
        }
    }

    virtual void dropEvent(QDropEvent* pe)
    {
        QList<QUrl> urlList = pe->mimeData()->urls();
        QString     file;

        m_newFiles.clear();
        foreach(QUrl url, urlList)
        {
            file = url.toString().remove(0, 7);
            if (!m_files.contains(file))
            {
                m_files.push_back(file);
                m_newFiles.push_back(file.section('/', -1));
                setText(text() + file + "\n");
            }
        }
        emit dropped();
    }

public:
    DropZone(QWidget* pwgt = 0) : QLabel("Drop Area", pwgt)
    {
        setAcceptDrops(true);
    }

    QStringList getFiles()
    {
        return (m_files);
    }

    QStringList getNewFiles()
    {
        return (m_newFiles);
    }
signals:
    void dropped();

};

#endif // DROPZONE_H
