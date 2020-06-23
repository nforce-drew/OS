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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyClient
{
public:

    void setupUi(QWidget *MyClient)
    {
        if (MyClient->objectName().isEmpty())
            MyClient->setObjectName(QString::fromUtf8("MyClient"));
        MyClient->resize(400, 300);

        retranslateUi(MyClient);

        QMetaObject::connectSlotsByName(MyClient);
    } // setupUi

    void retranslateUi(QWidget *MyClient)
    {
        MyClient->setWindowTitle(QApplication::translate("MyClient", "MyClient", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyClient: public Ui_MyClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLIENT_H
