#include "QueueTable.h"

QueueTable::QueueTable(QWidget *parent)
    : QTableWidget (parent)
{

}

void QueueTable::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "cool";
    QTableWidgetItem *targetItem = itemAt(event->pos());
    if (event->button() == Qt::LeftButton) {
        // включаем драг и дроп если ячейка выделена
        if (targetItem != 0)
        {
            if (targetItem->isSelected())
                setDragDropMode(QAbstractItemView::DragDrop);
            else
                setDragDropMode(QAbstractItemView::NoDragDrop);
        }
    }
    QTableWidget::mousePressEvent(event);
}

void QueueTable::moveEvent(QMoveEvent*    event)
{
    queueChanged();
    QTableWidget::moveEvent(event);
}

void QueueTable::dropEvent(QDropEvent *event)
{
    QTableWidgetItem*   targetItem;
    int                 countCol;
    int                 selRow;
    int                 targetRow;


    countCol = horizontalHeader()->count();
    // проверяем что источник - родная таблица
    if (event->source() != this)
    {
        qDebug() << "Неродной источник обработаем обработчиком по умолчанию";
        QTableWidget::dropEvent(event);
    }

    // определяем цель вставки
    targetItem = new QTableWidgetItem;
    targetItem = itemAt(event->pos());
    if (targetItem != 0)
        targetRow = targetItem->row();
    else
        targetRow = rowCount();

    if (selectedItems().isEmpty())
    {
        event->accept();  // не будем игнорить сообщение, скажем что обработали и передадим дальше
        return;
    }

    selRow = selectedItems()[0]->row();
    if (targetRow < selRow)
    {
        QStringList selRowData;
        for (int j = 0; j < countCol; j++)
            selRowData << item(selRow, j)->text();
        qDebug() << selRowData[0] << " " << selRowData[1];
        for (int i = 0; i < (selRow - targetRow); i++)
        {

            for (int j = 0; j < countCol; j++)
            {
                setItem(selRow - i, j, new QTableWidgetItem(item(selRow - i - 1, j)->text()));
            }
        }
        for (int j = 0; j < countCol; j++)
        {
            qDebug() << "j = " << j << " targetRow = " << targetRow << " selRowData[j] = " << selRowData[j];
            setItem(targetRow, j, new QTableWidgetItem(selRowData[j]));
        }
    }
    if (targetRow > selRow)
    {
        QStringList targetRowData;
        for (int j = 0; j < countCol; j++)
            targetRowData << item(targetRow, j)->text();
        qDebug() << targetRowData[0] << " " << targetRowData[1];
        for (int i = 0; i < (selRow - targetRow); i++)
        {
            for (int j = 0; j < countCol; j++)
            {
                setItem(selRow + i + 1, j, new QTableWidgetItem(item(selRow + i + 2, j)->text()));
            }
        }
        for (int j = 0; j < countCol; j++)
        {
            setItem(selRow, j, new QTableWidgetItem(targetRowData[j]));
        }
    }
//    QTableWidget::dropEvent(event);
    queueChanged();
}

void    QueueTable::queueChanged()
{
    int         rowCount;
    QStringList vertHdrList;

    rowCount = this->verticalHeader()->count();
    qDebug() << "slotQueueChanged()";
    for (int i = 0; i < rowCount; i++)
        vertHdrList << QString::number(i + 2);
    this->setVerticalHeaderLabels(vertHdrList);
}
