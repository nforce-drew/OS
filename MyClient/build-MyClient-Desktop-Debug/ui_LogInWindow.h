/********************************************************************************
** Form generated from reading UI file 'LogInWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogInWindow
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *main_VerticalLayout;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *login_verticalLayout;
    QLabel *login_label;
    QLineEdit *login_lineEdit;
    QVBoxLayout *password_verticalLayout;
    QLabel *password_label;
    QLineEdit *password_lineEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *error_lbl;
    QPushButton *signUp_btn;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *buttons_horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *login_btn;
    QPushButton *cancel_btn;

    void setupUi(QDialog *LogInWindow)
    {
        if (LogInWindow->objectName().isEmpty())
            LogInWindow->setObjectName(QString::fromUtf8("LogInWindow"));
        LogInWindow->resize(341, 243);
        layoutWidget = new QWidget(LogInWindow);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 20, 261, 207));
        main_VerticalLayout = new QVBoxLayout(layoutWidget);
        main_VerticalLayout->setObjectName(QString::fromUtf8("main_VerticalLayout"));
        main_VerticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        login_verticalLayout = new QVBoxLayout();
        login_verticalLayout->setObjectName(QString::fromUtf8("login_verticalLayout"));
        login_label = new QLabel(layoutWidget);
        login_label->setObjectName(QString::fromUtf8("login_label"));
        QFont font;
        font.setPointSize(10);
        login_label->setFont(font);

        login_verticalLayout->addWidget(login_label);

        login_lineEdit = new QLineEdit(layoutWidget);
        login_lineEdit->setObjectName(QString::fromUtf8("login_lineEdit"));
        QFont font1;
        font1.setPointSize(12);
        login_lineEdit->setFont(font1);

        login_verticalLayout->addWidget(login_lineEdit);


        verticalLayout->addLayout(login_verticalLayout);

        password_verticalLayout = new QVBoxLayout();
        password_verticalLayout->setObjectName(QString::fromUtf8("password_verticalLayout"));
        password_label = new QLabel(layoutWidget);
        password_label->setObjectName(QString::fromUtf8("password_label"));
        password_label->setFont(font);

        password_verticalLayout->addWidget(password_label);

        password_lineEdit = new QLineEdit(layoutWidget);
        password_lineEdit->setObjectName(QString::fromUtf8("password_lineEdit"));
        password_lineEdit->setFont(font1);

        password_verticalLayout->addWidget(password_lineEdit);


        verticalLayout->addLayout(password_verticalLayout);


        main_VerticalLayout->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        error_lbl = new QLabel(layoutWidget);
        error_lbl->setObjectName(QString::fromUtf8("error_lbl"));
        error_lbl->setContextMenuPolicy(Qt::CustomContextMenu);
        error_lbl->setStyleSheet(QString::fromUtf8("color: red;"));

        horizontalLayout->addWidget(error_lbl);

        signUp_btn = new QPushButton(layoutWidget);
        signUp_btn->setObjectName(QString::fromUtf8("signUp_btn"));
        signUp_btn->setLocale(QLocale(QLocale::Prussian, QLocale::World));

        horizontalLayout->addWidget(signUp_btn);


        main_VerticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        main_VerticalLayout->addItem(verticalSpacer);

        buttons_horizontalLayout = new QHBoxLayout();
        buttons_horizontalLayout->setObjectName(QString::fromUtf8("buttons_horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttons_horizontalLayout->addItem(horizontalSpacer);

        login_btn = new QPushButton(layoutWidget);
        login_btn->setObjectName(QString::fromUtf8("login_btn"));
        login_btn->setMinimumSize(QSize(0, 0));
        login_btn->setFont(font);
        login_btn->setCheckable(false);
        login_btn->setChecked(false);
        login_btn->setAutoRepeat(false);
        login_btn->setAutoExclusive(false);

        buttons_horizontalLayout->addWidget(login_btn);

        cancel_btn = new QPushButton(layoutWidget);
        cancel_btn->setObjectName(QString::fromUtf8("cancel_btn"));
        cancel_btn->setFont(font);

        buttons_horizontalLayout->addWidget(cancel_btn);


        main_VerticalLayout->addLayout(buttons_horizontalLayout);


        retranslateUi(LogInWindow);

        QMetaObject::connectSlotsByName(LogInWindow);
    } // setupUi

    void retranslateUi(QDialog *LogInWindow)
    {
        LogInWindow->setWindowTitle(QApplication::translate("LogInWindow", "Dialog", nullptr));
        login_label->setText(QApplication::translate("LogInWindow", "\320\233\320\276\320\263\320\270\320\275:", nullptr));
        password_label->setText(QApplication::translate("LogInWindow", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
        error_lbl->setText(QString());
        signUp_btn->setText(QApplication::translate("LogInWindow", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        login_btn->setText(QApplication::translate("LogInWindow", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        cancel_btn->setText(QApplication::translate("LogInWindow", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogInWindow: public Ui_LogInWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
