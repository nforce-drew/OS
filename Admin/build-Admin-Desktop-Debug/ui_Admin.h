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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QueueTable.h"

QT_BEGIN_NAMESPACE

class Ui_Admin
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *layout_main;
    QTabWidget *tabWidget;
    QWidget *tab_queue;
    QWidget *layoutWidget1;
    QVBoxLayout *layout_queue;
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
    QWidget *tab_userInfo;
    QWidget *layoutWidget2;
    QHBoxLayout *layout_userInfo;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *usersInfoTable;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *deleteUserBtn;
    QVBoxLayout *verticalLayout_2;
    QLabel *addLabel;
    QLabel *label;
    QLineEdit *editUsername;
    QLabel *label_3;
    QLineEdit *editPassword;
    QHBoxLayout *horizontalLayout_2;
    QLabel *errorAddUser_label;
    QPushButton *addBtn;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QComboBox *comboBox;
    QLabel *label_4;
    QLineEdit *editNewPassword;
    QHBoxLayout *horizontalLayout_4;
    QLabel *errorNewPass_label;
    QPushButton *newPassBtn;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QListWidget *binList;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *addBinBtn;
    QLabel *statusBar;

    void setupUi(QMainWindow *Admin)
    {
        if (Admin->objectName().isEmpty())
            Admin->setObjectName(QString::fromUtf8("Admin"));
        Admin->resize(984, 662);
        centralwidget = new QWidget(Admin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 761, 531));
        layout_main = new QVBoxLayout(layoutWidget);
        layout_main->setSpacing(6);
        layout_main->setContentsMargins(11, 11, 11, 11);
        layout_main->setObjectName(QString::fromUtf8("layout_main"));
        layout_main->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(layoutWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_queue = new QWidget();
        tab_queue->setObjectName(QString::fromUtf8("tab_queue"));
        layoutWidget1 = new QWidget(tab_queue);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 731, 441));
        layout_queue = new QVBoxLayout(layoutWidget1);
        layout_queue->setSpacing(6);
        layout_queue->setContentsMargins(11, 11, 11, 11);
        layout_queue->setObjectName(QString::fromUtf8("layout_queue"));
        layout_queue->setContentsMargins(20, 20, 20, 20);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        online_Layout = new QVBoxLayout();
        online_Layout->setSpacing(6);
        online_Layout->setObjectName(QString::fromUtf8("online_Layout"));
        Users_Lbl = new QLabel(layoutWidget1);
        Users_Lbl->setObjectName(QString::fromUtf8("Users_Lbl"));
        QFont font;
        font.setPointSize(15);
        Users_Lbl->setFont(font);

        online_Layout->addWidget(Users_Lbl);

        listUsers = new QListWidget(layoutWidget1);
        listUsers->setObjectName(QString::fromUtf8("listUsers"));

        online_Layout->addWidget(listUsers);


        horizontalLayout->addLayout(online_Layout);

        tasks_Layout = new QVBoxLayout();
        tasks_Layout->setSpacing(6);
        tasks_Layout->setObjectName(QString::fromUtf8("tasks_Layout"));
        Tasks_lbl = new QLabel(layoutWidget1);
        Tasks_lbl->setObjectName(QString::fromUtf8("Tasks_lbl"));
        QFont font1;
        font1.setPointSize(16);
        Tasks_lbl->setFont(font1);

        tasks_Layout->addWidget(Tasks_lbl);

        tableTasks = new QueueTable(layoutWidget1);
        tableTasks->setObjectName(QString::fromUtf8("tableTasks"));

        tasks_Layout->addWidget(tableTasks);


        horizontalLayout->addLayout(tasks_Layout);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);

        layout_queue->addLayout(horizontalLayout);

        btn_Layout = new QHBoxLayout();
        btn_Layout->setSpacing(6);
        btn_Layout->setObjectName(QString::fromUtf8("btn_Layout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        btn_Layout->addItem(horizontalSpacer);

        deleteBtn = new QPushButton(layoutWidget1);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));
        QFont font2;
        font2.setPointSize(10);
        deleteBtn->setFont(font2);

        btn_Layout->addWidget(deleteBtn);


        layout_queue->addLayout(btn_Layout);

        tabWidget->addTab(tab_queue, QString());
        tab_userInfo = new QWidget();
        tab_userInfo->setObjectName(QString::fromUtf8("tab_userInfo"));
        layoutWidget2 = new QWidget(tab_userInfo);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 10, 711, 441));
        layout_userInfo = new QHBoxLayout(layoutWidget2);
        layout_userInfo->setSpacing(6);
        layout_userInfo->setContentsMargins(11, 11, 11, 11);
        layout_userInfo->setObjectName(QString::fromUtf8("layout_userInfo"));
        layout_userInfo->setContentsMargins(10, 10, 10, 10);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(5, -1, -1, -1);
        usersInfoTable = new QTableWidget(layoutWidget2);
        usersInfoTable->setObjectName(QString::fromUtf8("usersInfoTable"));
        QFont font3;
        font3.setPointSize(12);
        usersInfoTable->setFont(font3);

        verticalLayout_4->addWidget(usersInfoTable);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        deleteUserBtn = new QPushButton(layoutWidget2);
        deleteUserBtn->setObjectName(QString::fromUtf8("deleteUserBtn"));
        QFont font4;
        font4.setPointSize(13);
        deleteUserBtn->setFont(font4);

        horizontalLayout_3->addWidget(deleteUserBtn);


        verticalLayout_4->addLayout(horizontalLayout_3);


        layout_userInfo->addLayout(verticalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(10, -1, 5, -1);
        addLabel = new QLabel(layoutWidget2);
        addLabel->setObjectName(QString::fromUtf8("addLabel"));
        QFont font5;
        font5.setPointSize(14);
        addLabel->setFont(font5);

        verticalLayout_2->addWidget(addLabel);

        label = new QLabel(layoutWidget2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font2);

        verticalLayout_2->addWidget(label);

        editUsername = new QLineEdit(layoutWidget2);
        editUsername->setObjectName(QString::fromUtf8("editUsername"));
        editUsername->setFont(font4);

        verticalLayout_2->addWidget(editUsername);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font2);

        verticalLayout_2->addWidget(label_3);

        editPassword = new QLineEdit(layoutWidget2);
        editPassword->setObjectName(QString::fromUtf8("editPassword"));
        editPassword->setFont(font4);

        verticalLayout_2->addWidget(editPassword);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        errorAddUser_label = new QLabel(layoutWidget2);
        errorAddUser_label->setObjectName(QString::fromUtf8("errorAddUser_label"));

        horizontalLayout_2->addWidget(errorAddUser_label);

        addBtn = new QPushButton(layoutWidget2);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));
        addBtn->setFont(font4);

        horizontalLayout_2->addWidget(addBtn);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setFont(font5);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(label_2);

        comboBox = new QComboBox(layoutWidget2);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setFont(font3);

        verticalLayout->addWidget(comboBox);

        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);

        verticalLayout->addWidget(label_4);

        editNewPassword = new QLineEdit(layoutWidget2);
        editNewPassword->setObjectName(QString::fromUtf8("editNewPassword"));
        editNewPassword->setFont(font4);

        verticalLayout->addWidget(editNewPassword);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        errorNewPass_label = new QLabel(layoutWidget2);
        errorNewPass_label->setObjectName(QString::fromUtf8("errorNewPass_label"));

        horizontalLayout_4->addWidget(errorNewPass_label);

        newPassBtn = new QPushButton(layoutWidget2);
        newPassBtn->setObjectName(QString::fromUtf8("newPassBtn"));
        newPassBtn->setFont(font4);

        horizontalLayout_4->addWidget(newPassBtn);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);


        layout_userInfo->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font5);

        verticalLayout_3->addWidget(label_5);

        binList = new QListWidget(layoutWidget2);
        binList->setObjectName(QString::fromUtf8("binList"));

        verticalLayout_3->addWidget(binList);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        addBinBtn = new QPushButton(layoutWidget2);
        addBinBtn->setObjectName(QString::fromUtf8("addBinBtn"));

        horizontalLayout_5->addWidget(addBinBtn);


        verticalLayout_3->addLayout(horizontalLayout_5);


        layout_userInfo->addLayout(verticalLayout_3);

        tabWidget->addTab(tab_userInfo, QString());

        layout_main->addWidget(tabWidget);

        statusBar = new QLabel(layoutWidget);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));

        layout_main->addWidget(statusBar);

        Admin->setCentralWidget(centralwidget);

        retranslateUi(Admin);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Admin);
    } // setupUi

    void retranslateUi(QMainWindow *Admin)
    {
        Admin->setWindowTitle(QApplication::translate("Admin", "Admin", nullptr));
        Users_Lbl->setText(QApplication::translate("Admin", "Online users", nullptr));
        Tasks_lbl->setText(QApplication::translate("Admin", "Tasks", nullptr));
        deleteBtn->setText(QApplication::translate("Admin", "Delete", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_queue), QApplication::translate("Admin", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\276\321\207\320\265\321\200\320\265\320\264\321\214\321\216", nullptr));
        deleteUserBtn->setText(QApplication::translate("Admin", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        addLabel->setText(QApplication::translate("Admin", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        label->setText(QApplication::translate("Admin", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        label_3->setText(QApplication::translate("Admin", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        errorAddUser_label->setText(QString());
        addBtn->setText(QApplication::translate("Admin", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        label_2->setText(QApplication::translate("Admin", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        comboBox->setItemText(0, QApplication::translate("Admin", "-\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217-", nullptr));

        label_4->setText(QApplication::translate("Admin", "\320\235\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        errorNewPass_label->setText(QString());
        newPassBtn->setText(QApplication::translate("Admin", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        label_5->setText(QApplication::translate("Admin", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\261\320\270\320\275\320\260\321\200\320\275\320\270\320\272\320\276\320\262", nullptr));
        addBinBtn->setText(QApplication::translate("Admin", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_userInfo), QApplication::translate("Admin", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\270", nullptr));
        statusBar->setText(QApplication::translate("Admin", "Status Bar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Admin: public Ui_Admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_H
