#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QMessageBox>

class login : QDialog
{
    Q_OBJECT

    public: explicit login(QWidget *parent = nullptr);

    private slots :
        void login_func();

    private :
        QLineEdit *loginEdit;
        QLineEdit *pwdEdit;
        QPushButton *loginButton;
        QPushButton *cancelButton;
}

#endif // LOGIN_H
