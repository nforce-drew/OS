/********************************************************************************
** Form generated from reading UI file 'Admin.ui'
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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QueueTable.h"

QT_BEGIN_NAMESPACE

class Ui_Admin
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *main_Layout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *online_Layout;
    QLabel *Users_Lbl;
    QListWidget *listUsers;
    QVBoxLayout *tasks_Layout;
    QLabel *Tasks_lbl;
    QueueTable *tableTasks;
    QHBoxLayout *btn_Layout;
    QSpacerItem *horizontalSpacer;
    QPushButton *deleteBtn;

    void setupUi(QMainWindow *Admin)
    {
        if (Admin->objectName().isEmpty())
            Admin->setObjectName(QStringLiteral("Admin"));
        Admin->resize(800, 470);
        centralwidget = new QWidget(Admin);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(41, 11, 731, 441));
        main_Layout = new QVBoxLayout(layoutWidget);
        main_Layout->setSpacing(6);
        main_Layout->setContentsMargins(11, 11, 11, 11);
        main_Layout->setObjectName(QStringLiteral("main_Layout"));
        main_Layout->setContentsMargins(20, 20, 20, 20);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        online_Layout = new QVBoxLayout();
        online_Layout->setSpacing(6);
        online_Layout->setObjectName(QStringLiteral("online_Layout"));
        Users_Lbl = new QLabel(layoutWidget);
        Users_Lbl->setObjectName(QStringLiteral("Users_Lbl"));
        QFont font;
        font.setPointSize(15);
        Users_Lbl->setFont(font);

        online_Layout->addWidget(Users_Lbl);

        listUsers = new QListWidget(layoutWidget);
        new QListWidgetItem(listUsers);
        new QListWidgetItem(listUsers);
        new QListWidgetItem(listUsers);
        listUsers->setObjectName(QStringLiteral("listUsers"));

        online_Layout->addWidget(listUsers);


        horizontalLayout->addLayout(online_Layout);

        tasks_Layout = new QVBoxLayout();
        tasks_Layout->setSpacing(6);
        tasks_Layout->setObjectName(QStringLiteral("tasks_Layout"));
        Tasks_lbl = new QLabel(layoutWidget);
        Tasks_lbl->setObjectName(QStringLiteral("Tasks_lbl"));
        QFont font1;
        font1.setPointSize(16);
        Tasks_lbl->setFont(font1);

        tasks_Layout->addWidget(Tasks_lbl);

        tableTasks = new QueueTable(layoutWidget);
        tableTasks->setObjectName(QStringLiteral("tableTasks"));

        tasks_Layout->addWidget(tableTasks);


        horizontalLayout->addLayout(tasks_Layout);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);

        main_Layout->addLayout(horizontalLayout);

        btn_Layout = new QHBoxLayout();
        btn_Layout->setSpacing(6);
        btn_Layout->setObjectName(QStringLiteral("btn_Layout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        btn_Layout->addItem(horizontalSpacer);

        deleteBtn = new QPushButton(layoutWidget);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));
        QFont font2;
        font2.setPointSize(10);
        deleteBtn->setFont(font2);

        btn_Layout->addWidget(deleteBtn);


        main_Layout->addLayout(btn_Layout);

        Admin->setCentralWidget(centralwidget);

        retranslateUi(Admin);

        QMetaObject::connectSlotsByName(Admin);
    } // setupUi

    void retranslateUi(QMainWindow *Admin)
    {
        Admin->setWindowTitle(QApplication::translate("Admin", "Admin", Q_NULLPTR));
        Users_Lbl->setText(QApplication::translate("Admin", "Online users", Q_NULLPTR));

        const bool __sortingEnabled = listUsers->isSortingEnabled();
        listUsers->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listUsers->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Admin", "User1", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem1 = listUsers->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("Admin", "User2", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem2 = listUsers->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("Admin", "User3", Q_NULLPTR));
        listUsers->setSortingEnabled(__sortingEnabled);

        Tasks_lbl->setText(QApplication::translate("Admin", "Tasks", Q_NULLPTR));
        deleteBtn->setText(QApplication::translate("Admin", "Delete", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Admin: public Ui_Admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_H
