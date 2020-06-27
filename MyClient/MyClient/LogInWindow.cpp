#include "LogInWindow.h"
#include "ui_LogInWindow.h"

LogInWindow::LogInWindow() {}

LogInWindow::LogInWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Images/Images/user.png"));
//    m_client = client;
    m_isSignIn = true;
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
    setWindowTitle("Авторизация");
    setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);

    LogInWindow::connect(ui->cancel_btn, SIGNAL(clicked())
                         , this, SLOT(slotCancelClicked()));
    LogInWindow::connect(ui->login_btn, SIGNAL(clicked())
                         , this, SLOT(slotCheckLogin()));
    connect(this, SIGNAL(logged()), this, SLOT(accept()));
}
//-----------------------------------------------------------------------
QString LogInWindow::getUserName()
{
    return (m_userName);
}
//-----------------------------------------------------------------------
void LogInWindow::changeToSignUp()
{
    m_isSignIn = false;
    setWindowTitle("Регистрация");
    ui->signUp_btn->setText("Назад");
    ui->login_btn->setText("Готово");
}
//-----------------------------------------------------------------------
void LogInWindow::changeToSignIn()
{
    m_isSignIn = true;
    setWindowTitle("Авторизация");
    ui->signUp_btn->setText("Регистрация");
    ui->login_btn->setText("Войти");
}
//-----------------------------------------------------------------------
void LogInWindow::slotCheckLogin()
{
    QString userName = ui->login_lineEdit   ->text();
    QString password = ui->password_lineEdit->text();
    m_userName = userName;

    ui->error_lbl->setText("");
    if (userName.size() > 19 || password.size() > 19)
        ui->error_lbl->setText("Пароль и логин\nне могут быть\nдлиннее 19 символов");
    LoginHeader loginHdr((char*)userName.toStdString().c_str(), (char*)password.toStdString().c_str());
    if (m_isSignIn)
        (qobject_cast<MyClient*>(this->parent()))->slotSendDataToServer(CHECK_LOGIN, (char*)&loginHdr, sizeof(loginHdr));
    else
        (qobject_cast<MyClient*>(this->parent()))->slotSendDataToServer(SIGN_UP, (char*)&loginHdr, sizeof(loginHdr));
    ui->password_lineEdit->clear();
}
//-----------------------------------------------------------------------
void LogInWindow::slotIncorrectLogin()
{
    ui->error_lbl->setText("Неверный логин или пароль!");
}
//-----------------------------------------------------------------------
void LogInWindow::slotCancelClicked()
{
    reject();
}
//-----------------------------------------------------------------------
LogInWindow::~LogInWindow()
{
    delete ui;
}
