#include "LogInWindow.h"
#include "ui_LogInWindow.h"

LogInWindow::LogInWindow() {}

LogInWindow::LogInWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInWindow)
{
    ui->setupUi(this);
//    m_client = client;
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
    setWindowTitle("Авторизация");
    setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);

    LogInWindow::connect(ui->cancel_btn, SIGNAL(clicked())
                         , this, SLOT(close()));
    LogInWindow::connect(ui->login_btn, SIGNAL(clicked())
                         , this, SLOT(slotCheckLogin()));
    connect(this, SIGNAL(logged()), this, SLOT(accept()));
}
//-----------------------------------------------------------------------
void LogInWindow::slotCheckLogin()
{
    connectDatabase();
    QString userName = ui->login_lineEdit   ->text();
    QString password = ui->password_lineEdit->text();
    m_userName = userName;

    LoginHeader loginHdr((char*)userName.toStdString().c_str(), (char*)password.toStdString().c_str());
    (qobject_cast<MyClient*>(this->parent()))->slotSendDataToServer(CHECK_LOGIN, (char*)&loginHdr, sizeof(loginHdr));
//    qobject_cast<MyClient*>(this->parent());
//    emit logged();

//    QSqlQuery myQ(db);
//    myQ.exec("SELECT user_name FROM users_info WHERE user_name = '" + userName + "'");
//    if(myQ.first() != false)
//    {
//        myQ.exec("SELECT user_password FROM users_info WHERE user_password = '" + password + "'");
//        if(myQ.first() != false)
//        {
//            hide();
//            myQ.exec("SELECT * FROM users_info WHERE user_name = '" + userName + "'");
//            QSqlRecord rec;
//            myQ.next();
//            rec = myQ.record();
//            m_userName = rec.value(0).toString();
//            LoginHeader loginHdr(userName, password);
//            slotSendDataToServer(CHECK_LOGIN, (char*)&loginHdr, sizeof(loginHdr));
//            emit logged();
//            this->parentWidget()->show();
//        }
//        else
//            ui->error_lbl->setText("Неверный логин или пароль!");
//    }
//    else
//        ui->error_lbl->setText("Неверный пароль или логин!");
    ui->password_lineEdit->clear();
}
//-----------------------------------------------------------------------
void LogInWindow::slotIncorrectLogin()
{
    ui->error_lbl->setText("Неверный логин или пароль!");
}
//-----------------------------------------------------------------------
void LogInWindow::connectDatabase()
{
    if(!db.isOpen())
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/home/nforce/OS/tasks_solver.db");
        db.open();
    }
    if(!db.isOpen())
    {
        QMessageBox::critical(this, "Ошибка", "База данных не открыта");
        close();
    }
}
//-----------------------------------------------------------------------
QString LogInWindow::getUserName()
{
    return (m_userName);
}
//-----------------------------------------------------------------------
LogInWindow::~LogInWindow()
{
    delete ui;
}
