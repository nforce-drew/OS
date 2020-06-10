/********************************************************************************
** Form generated from reading UI file 'admin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMIN_H
#define UI_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Admin
{
public:
    QWidget *centralwidget;
    QListWidget *listUsers;
    QLabel *Users_Lbl;
    QLabel *Tasks_lbl;
    QPushButton *deleteBtn;
    QTableWidget *tableTasks;

    void setupUi(QMainWindow *Admin)
    {
        if (Admin->objectName().isEmpty())
            Admin->setObjectName(QStringLiteral("Admin"));
        Admin->resize(800, 470);
        centralwidget = new QWidget(Admin);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        listUsers = new QListWidget(centralwidget);
        new QListWidgetItem(listUsers);
        new QListWidgetItem(listUsers);
        new QListWidgetItem(listUsers);
        listUsers->setObjectName(QStringLiteral("listUsers"));
        listUsers->setGeometry(QRect(40, 40, 161, 381));
        Users_Lbl = new QLabel(centralwidget);
        Users_Lbl->setObjectName(QStringLiteral("Users_Lbl"));
        Users_Lbl->setGeometry(QRect(80, 10, 121, 31));
        QFont font;
        font.setPointSize(15);
        Users_Lbl->setFont(font);
        Tasks_lbl = new QLabel(centralwidget);
        Tasks_lbl->setObjectName(QStringLiteral("Tasks_lbl"));
        Tasks_lbl->setGeometry(QRect(470, 10, 101, 31));
        QFont font1;
        font1.setPointSize(16);
        Tasks_lbl->setFont(font1);
        deleteBtn = new QPushButton(centralwidget);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));
        deleteBtn->setGeometry(QRect(670, 430, 93, 28));
        QFont font2;
        font2.setPointSize(10);
        deleteBtn->setFont(font2);
        tableTasks = new QTableWidget(centralwidget);
        if (tableTasks->columnCount() < 3)
            tableTasks->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableTasks->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableTasks->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableTasks->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableTasks->rowCount() < 3)
            tableTasks->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableTasks->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableTasks->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableTasks->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableTasks->setItem(0, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableTasks->setItem(0, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableTasks->setItem(0, 2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableTasks->setItem(1, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableTasks->setItem(1, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableTasks->setItem(1, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableTasks->setItem(2, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableTasks->setItem(2, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableTasks->setItem(2, 2, __qtablewidgetitem14);
        tableTasks->setObjectName(QStringLiteral("tableTasks"));
        tableTasks->setGeometry(QRect(260, 50, 511, 371));
        Admin->setCentralWidget(centralwidget);

        retranslateUi(Admin);

        QMetaObject::connectSlotsByName(Admin);
    } // setupUi

    void retranslateUi(QMainWindow *Admin)
    {
        Admin->setWindowTitle(QApplication::translate("Admin", "Admin", Q_NULLPTR));

        const bool __sortingEnabled = listUsers->isSortingEnabled();
        listUsers->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listUsers->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Admin", "User1", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem1 = listUsers->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("Admin", "User2", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem2 = listUsers->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("Admin", "User3", Q_NULLPTR));
        listUsers->setSortingEnabled(__sortingEnabled);

        Users_Lbl->setText(QApplication::translate("Admin", "Users", Q_NULLPTR));
        Tasks_lbl->setText(QApplication::translate("Admin", "Tasks", Q_NULLPTR));
        deleteBtn->setText(QApplication::translate("Admin", "Delete", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableTasks->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Admin", "Task", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableTasks->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Admin", "User", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableTasks->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Admin", "Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableTasks->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("Admin", "  1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableTasks->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("Admin", "  2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableTasks->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("Admin", "  3", Q_NULLPTR));

        const bool __sortingEnabled1 = tableTasks->isSortingEnabled();
        tableTasks->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = tableTasks->item(0, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("Admin", "Task1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableTasks->item(0, 1);
        ___qtablewidgetitem7->setText(QApplication::translate("Admin", "User2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableTasks->item(0, 2);
        ___qtablewidgetitem8->setText(QApplication::translate("Admin", "11:11:11", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableTasks->item(1, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("Admin", "Task2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableTasks->item(1, 1);
        ___qtablewidgetitem10->setText(QApplication::translate("Admin", "User1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableTasks->item(1, 2);
        ___qtablewidgetitem11->setText(QApplication::translate("Admin", "13:45:31", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableTasks->item(2, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("Admin", "Task3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableTasks->item(2, 1);
        ___qtablewidgetitem13->setText(QApplication::translate("Admin", "User3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tableTasks->item(2, 2);
        ___qtablewidgetitem14->setText(QApplication::translate("Admin", "17:12:13", Q_NULLPTR));
        tableTasks->setSortingEnabled(__sortingEnabled1);

    } // retranslateUi

};

namespace Ui {
    class Admin: public Ui_Admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_H
