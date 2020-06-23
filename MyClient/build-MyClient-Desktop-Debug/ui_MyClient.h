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
#include "DropZone.h"

QT_BEGIN_NAMESPACE

class Ui_MyClient
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    DropZone *dropArea;
    QListWidget *filesList;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *solveBtn;
    QLabel *statusBar;

    void setupUi(QWidget *MyClient)
    {
        if (MyClient->objectName().isEmpty())
            MyClient->setObjectName(QString::fromUtf8("MyClient"));
        MyClient->resize(645, 473);
        widget = new QWidget(MyClient);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 20, 621, 321));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        dropArea = new DropZone(widget);
        dropArea->setObjectName(QString::fromUtf8("dropArea"));
        dropArea->setFrameShape(QFrame::Box);

        horizontalLayout->addWidget(dropArea);

        filesList = new QListWidget(widget);
        filesList->setObjectName(QString::fromUtf8("filesList"));

        horizontalLayout->addWidget(filesList);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        solveBtn = new QPushButton(widget);
        solveBtn->setObjectName(QString::fromUtf8("solveBtn"));

        horizontalLayout_2->addWidget(solveBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        statusBar = new QLabel(widget);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));

        verticalLayout->addWidget(statusBar);


        retranslateUi(MyClient);

        QMetaObject::connectSlotsByName(MyClient);
    } // setupUi

    void retranslateUi(QWidget *MyClient)
    {
        MyClient->setWindowTitle(QApplication::translate("MyClient", "MyClient", nullptr));
        dropArea->setText(QApplication::translate("MyClient", "TextLabel", nullptr));
        solveBtn->setText(QApplication::translate("MyClient", "\320\240\320\265\321\210\320\270\321\202\321\214", nullptr));
        statusBar->setText(QApplication::translate("MyClient", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyClient: public Ui_MyClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLIENT_H
