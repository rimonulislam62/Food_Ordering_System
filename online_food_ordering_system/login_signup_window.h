#ifndef LOGIN_SIGNUP_WINDOW_H
#define LOGIN_SIGNUP_WINDOW_H

#include <QMainWindow>
#include <customers.h>
#include <vendors.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>
#include <QMessageBox>

namespace Ui {
class login_signup_window;
}

class login_signup_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit login_signup_window(QWidget *parent = nullptr,int x=0);
    ~login_signup_window();
public:
    int f;
    void Database_open();

private slots:
    void on_pushButton_2_login_clicked();

    void on_pushButton_3_signup_in_login_clicked();

    void on_pushButton_signup_in_signup_clicked();

    void on_pushButton_return_in_login_clicked();

    void on_pushButton_return_in_signup_clicked();

private:
    Ui::login_signup_window *ui;
    QString mobile, password;
    QSqlDatabase database;
    customers *customer;
    vendors *vendor;
};

#endif // LOGIN_SIGNUP_WINDOW_H
