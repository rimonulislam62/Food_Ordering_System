#ifndef PROFILE_H
#define PROFILE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>
#include<QFileInfo>
#include<QPushButton>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QVBoxLayout>
#include<QString>
#include<QFrame>



namespace Ui {
class profile;
}

class profile : public QMainWindow
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr,QString mobile=NULL,int x=0);
    ~profile();
public:
    QString mobiles;
    int f;
    void Database_open();
    void show_profile();

private slots:

    void checkhistory();

    void on_pushButton_4_confirm_in_update_clicked();

    void on_pushButton_profile_clicked();

    void on_pushButton_2_update_profile_clicked();

    void on_pushButton_3_return_clicked();

private:
    Ui::profile *ui;
    QSqlDatabase prodb;
};

#endif // PROFILE_H
