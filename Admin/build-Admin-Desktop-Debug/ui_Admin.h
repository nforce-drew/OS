/********************************************************************************
** Form generated from reading UI file 'Admin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMIN_H
#define UI_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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
    QLabel *statusBar;

    void setupUi(QMainWindow *Admin)
    {
        if (Admin->objectName().isEmpty())
            Admin->setObjectName(QString::fromUtf8("Admin"));
        Admin->resize(800, 470);
        centralwidget = new QWidget(Admin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(41, 11, 731, 441));
        main_Layout = new QVBoxLayout(layoutWidget);
        main_Layout->setSpacing(6);
        main_Layout->setContentsMargins(11, 11, 11, 11);
        main_Layout->setObjectName(QString::fromUtf8("main_Layout"));
        main_Layout->setContentsMargins(20, 20, 20, 20);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        online_Layout = new QVBoxLayout();
        online_Layout->setSpacing(6);
        online_Layout->setObjectName(QString::fromUtf8("online_Layout"));
        Users_Lbl = new QLabel(layoutWidget);
        Users_Lbl->setObjectName(QString::fromUtf8("Users_Lbl"));
        QFont font;
        font.setPointSize(15);
        Users_Lbl->setFont(font);

        online_Layout->addWidget(Users_Lbl);

        listUsers = new QListWidget(layoutWidget);
        listUsers->setObjectName(QString::fromUtf8("listUsers"));

        online_Layout->addWidget(listUsers);


        horizontalLayout->addLayout(online_Layout);

        tasks_Layout = new QVBoxLayout();
        tasks_Layout->setSpacing(6);
        tasks_Layout->setObjectName(QString::fromUtf8("tasks_Layout"));
        Tasks_lbl = new QLabel(layoutWidget);
        Tasks_lbl->setObjectName(QString::fromUtf8("Tasks_lbl"));
        QFont font1;
        font1.setPointSize(16);
        Tasks_lbl->setFont(font1);

        tasks_Layout->addWidget(Tasks_lbl);

        tableTasks = new QueueTable(layoutWidget);
        tableTasks->setObjectName(QString::fromUtf8("tableTasks"));

        tasks_Layout->addWidget(tableTasks);


        horizontalLayout->addLayout(tasks_Layout);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);

        main_Layout->addLayout(horizontalLayout);

        btn_Layout = new QHBoxLayout();
        btn_Layout->setSpacing(6);
        btn_Layout->setObjectName(QString::fromUtf8("btn_Layout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        btn_Layout->addItem(horizontalSpacer);

        deleteBtn = new QPushButton(layoutWidget);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));
        QFont font2;
        font2.setPointSize(10);
        deleteBtn->setFont(font2);

        btn_Layout->addWidget(deleteBtn);


        main_Layout->addLayout(btn_Layout);

        statusBar = new QLabel(layoutWidget);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));

        main_Layout->addWidget(statusBar);

        Admin->setCentralWidget(centralwidget);

        retranslateUi(Admin);

        QMetaObject::connectSlotsByName(Admin);
    } // setupUi

    void retranslateUi(QMainWindow *Admin)
    {
        Admin->setWindowTitle(QApplication::translate("Admin", "Admin", nullptr));
        Users_Lbl->setText(QApplication::translate("Admin", "Online users", nullptr));
        Tasks_lbl->setText(QApplication::translate("Admin", "Tasks", nullptr));
        deleteBtn->setText(QApplication::translate("Admin", "Delete", nullptr));
        statusBar->setText(QApplication::translate("Admin", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Admin: public Ui_Admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_H
