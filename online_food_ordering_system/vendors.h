#ifndef VENDORS_H
#define VENDORS_H

#include <QMainWindow>
#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>
#include<QFileInfo>
#include<QWidget>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QVBoxLayout>
#include<QString>
#include<QFrame>
#include<profile.h>

namespace Ui {
class vendors;
}

class vendors : public QMainWindow
{
    Q_OBJECT
public:
    static int y;
      int z;
    QString mobile;
    void Database_open();
    void Scroll_Area();
public slots:
    void onnameclicked();
public:

    explicit vendors(QWidget *parent = nullptr,QString mobile_num=NULL,int x=0);
    ~vendors();

private slots:
    void on_pushButton_add_Food_clicked();

    void on_pushButton_2_remove_food_clicked();

    void on_pushButton_add_food_clicked();

    void on_pushButton_remove_food_clicked();

    void on_pushButton_add_photo_clicked();

    void on_pushButton_logout_in_page1_clicked();

    void on_pushButton_return_button_in_page2_clicked();

    void on_pushButton_return_button_in_page3_clicked();

    void on_pushButton_vendor_profile_clicked();

private:
    Ui::vendors *ui;
    QSqlDatabase db;
    profile *proV;
};



#endif // VENDORS_H
