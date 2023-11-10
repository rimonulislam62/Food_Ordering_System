#include "login_signup_window.h"
#include "ui_login_signup_window.h"
#include <mainwindow.h>
#include <QtSql/QSqlQuery>
#include <QMessageBox>

MainWindow *c;
login_signup_window::login_signup_window(QWidget *parent,int x) :
    QMainWindow(parent),
    ui(new Ui::login_signup_window)
{
    ui->setupUi(this);
    f=x;
    Database_open();
    ui->stackedWidget->setCurrentIndex(0);

}

login_signup_window::~login_signup_window()
{
    database.close();
    database.removeDatabase(QSqlDatabase::defaultConnection);
    delete ui;
}

//function for database opening:
void login_signup_window::Database_open()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("D:/New folder/online-food-ordering-system-in-QT-main/online_food_ordering_system/online_food_ordering_system/resources/online_food_ordering_system.db");
    if(database.open())
    {
        qDebug()<<"open!";
    }
    else
    {
        qDebug()<<"fail to open!!";
    }
}

//this is login button's work:
void login_signup_window::on_pushButton_2_login_clicked()
{
    qDebug()<<f;
    mobile = ui->lineEdit_login_mobile->text();
    password = ui->lineEdit_2_login_password->text();
    QSqlQuery qry;
    if(f==1)
    {
        qry.exec("select * from customer_login_info where Mobile_num='"+mobile+"' AND Password='"+password+"';");
        if(qry.next())
        {
            qDebug()<<"you are in";
            database.close();
            database.removeDatabase(QSqlDatabase::defaultConnection);
            this->hide();
            customer = new customers(this,mobile,f);
            customer->show();
        }
        else
        {
            qDebug()<<"you are not in";
            QMessageBox::warning(this,"Login fail !","Wrong credential");
        }

    }
    else if(f==2)
    {
        qry.exec("select * from vendor_login_info where Mobile_num='"+mobile+"' AND Password='"+password+"';");
        if(qry.next())
        {
            qDebug()<<"you are in";
            database.close();
            database.removeDatabase(QSqlDatabase::defaultConnection);
            this->hide();
            vendor = new vendors(this,mobile,f);
            vendor->show();
        }
        else
        {
            qDebug()<<"you are not in";
            QMessageBox::warning(this,"Login fail !","Wrong credential");
        }

    }

}

//sign up button in login_page-> this button will change the ui to sign up page.
void login_signup_window::on_pushButton_3_signup_in_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    if(f==2){
        ui->lineEdit_name->setPlaceholderText("Store's Name");
        ui->lineEdit_4_address->setPlaceholderText("Store's Address in details");
    }
    else{
        ui->lineEdit_name->setPlaceholderText("Customer's Name");
        ui->lineEdit_4_address->setPlaceholderText("Home Address in details");
    }
}

//sign up button-> this will create a new account.
void login_signup_window::on_pushButton_signup_in_signup_clicked()
{
    QString name, address;
    mobile = ui->lineEdit_2_mobile->text();
    password = ui->lineEdit_3_password->text();
    name = ui->lineEdit_name->text();
    address = ui->lineEdit_4_address->text();
    if(mobile.isEmpty() || password.isEmpty() || name.isEmpty() || address.isEmpty())
    {
        QMessageBox::warning(this,"Fill all data","please fill up all the information.");
    }
    else
    {
        QSqlQuery qry;
        if(f==1)
        {
            qry.prepare("INSERT INTO customer_login_info(Mobile_num, Password, Name,Address)"
                         "VALUES(?,?,?,?);");
        }
        else
        {
            qry.prepare("INSERT INTO vendor_login_info(Mobile_num, Password, Restaurent,Address)"
                        "VALUES(?,?,?,?);");
        }
        qry.addBindValue(mobile);
        qry.addBindValue(password);
        qry.addBindValue(name);
        qry.addBindValue(address);
        if(qry.exec())
        {
            qDebug()<<"data insertion is a success!";
            ui->stackedWidget->setCurrentIndex(0);
        }
        else
        {
            qDebug()<<"Data insertion failed!!";
        }

    }
}

//return button->change ui to the main window.
void login_signup_window::on_pushButton_return_in_login_clicked()
{
    this->hide();
    database.close();
    database.removeDatabase(QSqlDatabase::defaultConnection);
    c = new MainWindow(this);
    c->show();
}

//return button-> change ui to the login page.
void login_signup_window::on_pushButton_return_in_signup_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
