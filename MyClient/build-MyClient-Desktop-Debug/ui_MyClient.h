/********************************************************************************
** Form generated from reading UI file 'MyClient.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCLIENT_H
#define UI_MYCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "DropArea.h"

QT_BEGIN_NAMESPACE

class Ui_MyClient
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *userName;
    QHBoxLayout *horizontalLayout;
    QListWidget *tasksList;
    DropArea *dropArea;
    QVBoxLayout *verticalLayout_2;
    QListWidget *filesList;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *deleteFileBtn;
    QPushButton *solveBtn;
    QLabel *statusBar;

    void setupUi(QWidget *MyClient)
    {
        if (MyClient->objectName().isEmpty())
            MyClient->setObjectName(QString::fromUtf8("MyClient"));
        MyClient->resize(753, 414);
        layoutWidget = new QWidget(MyClient);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 675, 321));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        userName = new QLabel(layoutWidget);
        userName->setObjectName(QString::fromUtf8("userName"));

        verticalLayout->addWidget(userName);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tasksList = new QListWidget(layoutWidget);
        tasksList->setObjectName(QString::fromUtf8("tasksList"));
        tasksList->setMinimumSize(QSize(290, 0));

        horizontalLayout->addWidget(tasksList);

        dropArea = new DropArea(layoutWidget);
        dropArea->setObjectName(QString::fromUtf8("dropArea"));
        dropArea->setFrameShape(QFrame::Box);
        dropArea->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(dropArea);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        filesList = new QListWidget(layoutWidget);
        filesList->setObjectName(QString::fromUtf8("filesList"));

        verticalLayout_2->addWidget(filesList);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_2->addWidget(comboBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        deleteFileBtn = new QPushButton(layoutWidget);
        deleteFileBtn->setObjectName(QString::fromUtf8("deleteFileBtn"));

        horizontalLayout_2->addWidget(deleteFileBtn);

        solveBtn = new QPushButton(layoutWidget);
        solveBtn->setObjectName(QString::fromUtf8("solveBtn"));

        horizontalLayout_2->addWidget(solveBtn);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 1);

        verticalLayout->addLayout(horizontalLayout);

        statusBar = new QLabel(layoutWidget);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));

        verticalLayout->addWidget(statusBar);


        retranslateUi(MyClient);

        QMetaObject::connectSlotsByName(MyClient);
    } // setupUi

    void retranslateUi(QWidget *MyClient)
    {
        MyClient->setWindowTitle(QApplication::translate("MyClient", "MyClient", nullptr));
        userName->setText(QString());
        dropArea->setText(QApplication::translate("MyClient", "\320\237\320\265\321\200\320\265\321\202\320\260\321\211\320\270\321\202\320\265 \321\204\320\260\320\271\320\273\321\213 \321\201\321\216\320\264\320\260", nullptr));
        deleteFileBtn->setText(QApplication::translate("MyClient", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        solveBtn->setText(QApplication::translate("MyClient", "\320\240\320\265\321\210\320\270\321\202\321\214", nullptr));
        statusBar->setText(QApplication::translate("MyClient", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyClient: public Ui_MyClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLIENT_H
