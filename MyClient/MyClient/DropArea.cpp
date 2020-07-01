#include "DropArea.h"


int DropArea::deleteFile(QString fileName)
{
    QStringList fileNames;

    for (auto filePath : m_files)
        fileNames.push_back(filePath.section('/', -1));
    if (fileNames.contains(fileName))
    {
        int i = 0;
        for (auto el : fileNames)
        {
            if (el == fileName)
            {
                m_files.removeAt(i);
                return (i);
            }
            i++;
        }
    }
    return (0);
}

DropArea::DropArea(QWidget *pwgt): QLabel("Drop Area", pwgt)
{
    setAcceptDrops(true);
}

QStringList DropArea::getFiles()
{
    return (m_files);
}

void DropArea::clearFiles()
{
    m_files.clear();
}


void DropArea::dragEnterEvent(QDragEnterEvent *pe)
{
    if (pe->mimeData()->hasFormat("text/uri-list"))
        pe->acceptProposedAction();
}

void DropArea::dropEvent(QDropEvent *pe)
{
    QList<QUrl> urlList = pe->mimeData()->urls();
    QString     file;
    QStringList newFiles;

    qDebug() << "dropEvent";
    foreach(QUrl url, urlList)
    {
        file = url.toString().remove(0, 7);
        if (!m_files.contains(file))
        {
            m_files.push_back(file);
            newFiles.push_back(file.section('/', -1));
        }
    }
    emit dropped(newFiles);
}
