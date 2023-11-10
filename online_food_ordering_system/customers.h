#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <QMainWindow>
#include <profile.h>
#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>
#include<QFileInfo>
#include<QGridLayout>
#include<QWidget>
#include<QPushButton>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QVBoxLayout>
#include<QString>
#include<QFrame>


namespace Ui {
class customers;
}

class customers : public QMainWindow
{
    Q_OBJECT
public:
    int k;
    static int x;
    void Scroll_Area();

    void Database_open();
public slots:
    void onnameclicked();
public:
    explicit customers(QWidget *parent = nullptr,QString mobile_num = NULL,int x=0);
    ~customers();

private slots:
    void on_pushButton_order_place_clicked();

    void on_pushButton_log_out_clicked();



    void on_pushButton_2_profile_clicked();

private:
    Ui::customers *ui;
    QSqlDatabase mydb;
    QString mobile;
    profile *pro;
};

#endif // CUSTOMERS_H
