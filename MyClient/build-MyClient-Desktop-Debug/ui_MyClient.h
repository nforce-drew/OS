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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "DropArea.h"

QT_BEGIN_NAMESPACE

class Ui_MyClient
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QListWidget *tasksList;
    DropArea *dropArea;
    QListWidget *filesList;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *solveBtn;
    QLabel *statusBar;

    void setupUi(QWidget *MyClient)
    {
        if (MyClient->objectName().isEmpty())
            MyClient->setObjectName(QString::fromUtf8("MyClient"));
        MyClient->resize(753, 414);
        layoutWidget = new QWidget(MyClient);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 671, 321));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tasksList = new QListWidget(layoutWidget);
        tasksList->setObjectName(QString::fromUtf8("tasksList"));
        tasksList->setMinimumSize(QSize(280, 0));

        horizontalLayout->addWidget(tasksList);

        dropArea = new DropArea(layoutWidget);
        dropArea->setObjectName(QString::fromUtf8("dropArea"));
        dropArea->setFrameShape(QFrame::Box);

        horizontalLayout->addWidget(dropArea);

        filesList = new QListWidget(layoutWidget);
        filesList->setObjectName(QString::fromUtf8("filesList"));

        horizontalLayout->addWidget(filesList);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        solveBtn = new QPushButton(layoutWidget);
        solveBtn->setObjectName(QString::fromUtf8("solveBtn"));

        horizontalLayout_2->addWidget(solveBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        statusBar = new QLabel(layoutWidget);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));

        verticalLayout->addWidget(statusBar);


        retranslateUi(MyClient);

        QMetaObject::connectSlotsByName(MyClient);
    } // setupUi

    void retranslateUi(QWidget *MyClient)
    {
        MyClient->setWindowTitle(QApplication::translate("MyClient", "MyClient", nullptr));
        dropArea->setText(QApplication::translate("MyClient", "DROP AREA", nullptr));
        solveBtn->setText(QApplication::translate("MyClient", "\320\240\320\265\321\210\320\270\321\202\321\214", nullptr));
        statusBar->setText(QApplication::translate("MyClient", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyClient: public Ui_MyClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLIENT_H
