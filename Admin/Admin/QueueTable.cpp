#include "QueueTable.h"

QueueTable::QueueTable(QWidget *parent)
    : QTableWidget (parent)
{
    queueList = new QList<QueueHeader>;
}

void QueueTable::mousePressEvent(QMouseEvent *event)
{
    QTableWidgetItem *targetItem = itemAt(event->pos());
    if (event->button() == Qt::LeftButton) {
        // включаем драг и дроп если ячейка выделена
        if (targetItem != 0)
        {
            qDebug() << "cool";
            if (targetItem->isSelected())
            {
                setDragDropMode(QAbstractItemView::DragDrop);

            }
            else
                setDragDropMode(QAbstractItemView::NoDragDrop);
        }
    }
    QTableWidget::mousePressEvent(event);
}

void QueueTable::dropEvent(QDropEvent *event)
{
    QTableWidgetItem*   targetItem;
    QStringList         selRowData;
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
    // Запрет замены первой задачи
    if (targetRow == 0)
    {
        QMessageBox::warning(0, "Ошибка", "Невозможно заменить первую задачу. Преостановите решение задачи.");
        event->accept();  // не будем игнорить сообщение, скажем что обработали и передадим дальше
        return;
    }

    if (selectedItems().isEmpty())
    {
        event->accept();  // не будем игнорить сообщение, скажем что обработали и передадим дальше
        return;
    }

    selRow = selectedItems()[0]->row();
    if (selRow == targetRow)
    {
        event->accept();  // не будем игнорить сообщение, скажем что обработали и передадим дальше
        return;
    }
    //Запрет перемещения первой задачи
    if (selRow == 0)
    {
        QMessageBox::warning(0, "Ошибка", "Невозможно переместить первую задачу. Преостановите решение задачи.");
        event->accept();  // не будем игнорить сообщение, скажем что обработали и передадим дальше
        return;
    }

    for (int j = 0; j < countCol; j++)
        selRowData << item(selRow, j)->text();

    if (targetRow < selRow)
    {
        qDebug() << selRowData[0] << " " << selRowData[1];
        for (int i = 0; i < (selRow - targetRow); i++)
            for (int j = 0; j < countCol; j++)
                setItem(selRow - i, j, new QTableWidgetItem(item(selRow - i - 1, j)->text()));
        for (int j = 0; j < countCol; j++)
        {
            qDebug() << "j = " << j << " targetRow = " << targetRow << " selRowData[j] = " << selRowData[j];
            setItem(targetRow, j, new QTableWidgetItem(selRowData[j]));
        }
    }

    if (targetRow > selRow)
    {
        for (int i = 0; i < (targetRow - selRow); i++)
            for (int j = 0; j < countCol; j++)
                setItem(selRow + i, j, new QTableWidgetItem(item(selRow + i + 1, j)->text()));
        for (int j = 0; j < countCol; j++)
            setItem(targetRow, j, new QTableWidgetItem(selRowData[j]));
    }
    setCurrentCell(targetRow, 0);
    queueChanged();
    emit queueChanged(queueList);
}

void    QueueTable::queueChanged()
{
    int         rowCount;
    QStringList vertHdrList;

    rowCount = this->verticalHeader()->count();
    qDebug() << "slotQueueChanged()";
    for (int i = 0; i < rowCount; i++)
        vertHdrList << QString::number(i + 1);
    this->setVerticalHeaderLabels(vertHdrList);
}

QueueTable::~QueueTable()
{
    delete queueList;
}
