#include "profile.h"
#include "ui_profile.h"
#include<customers.h>
#include<vendors.h>
#include<QMessageBox>

customers *rcustomer;
vendors *rvendor;

profile::profile(QWidget *parent,QString mobile,int x) :
    QMainWindow(parent),
    ui(new Ui::profile)
{
    ui->setupUi(this);
    mobiles = mobile;
    f = x;
    Database_open();
    ui->stackedWidget->setCurrentIndex(0);
    show_profile();
}

profile::~profile()
{
    prodb.close();
    prodb.removeDatabase(QSqlDatabase::defaultConnection);
    delete ui;
}

void profile::Database_open()
{
    prodb = QSqlDatabase::addDatabase("QSQLITE");
    prodb.setDatabaseName("D:/New folder/online-food-ordering-system-in-QT-main/online_food_ordering_system/online_food_ordering_system/resources/online_food_ordering_system.db");
    if(prodb.open())
    {
        qDebug()<<"open!";
    }
    else
    {
        qDebug()<<"fail to open!!";
    }

}

void profile::show_profile()
{
    QString str1,str2,str3;
    QSqlQuery qry1;

    qDebug()<<mobiles<<"--"<<f;

    if(f==1)
    {
        qDebug()<<"inside";
        QPushButton *history = new QPushButton("History",this);
        history->setGeometry(0,250,121,41);
        history->setStyleSheet("QPushButton{font: 10pt 'Countryside two';border:3px dashed white;border-radius:30px;background-color:#231f1f;color:white;}"
                               "QPushButton:hover{font:12pt;color:red;border-color: orange;}");

        qDebug()<<qry1.exec("select * from customer_login_info where Mobile_num='"+mobiles+"'");
        if(qry1.next())
        {
            str1 = qry1.value("Name").toString();
            str2 = qry1.value("Mobile_num").toString();
            str3 = qry1.value("Address").toString();
        }
        //model1 -> setQuery(*qry1)

        history->show();
        connect(history,SIGNAL(clicked()),this,SLOT(checkhistory()));
    }
    else if(f==2)
    {
        //Restaurent
        qDebug()<<qry1.exec("select * from vendor_login_info where Mobile_num='"+mobiles+"'");
        if(qry1.next())
        {
            str1 = qry1.value("Restaurent").toString();
            str2 = qry1.value("Mobile_num").toString();
            str3 = qry1.value("Address").toString();
        }
    }

    qDebug()<<str1<<str2<<str3;
    ui->label_4_name->setText(str1);
    ui->label_5_mobile->setText(str2);
    ui->textEdit_address->setPlainText(str3);

}


void profile::checkhistory()
{
    ui->stackedWidget->setCurrentIndex(2);
    QVBoxLayout *lay = new QVBoxLayout(this);

    QSqlQueryModel *model1 = new QSqlQueryModel();
    QSqlQueryModel *model2 = new QSqlQueryModel();

    QSqlQuery *qry1 = new QSqlQuery(prodb);
    QFrame *frame[20];


    qDebug()<<qry1->exec("select * from History where Mobile_num='"+mobiles+"'");



    model1 -> setQuery(*qry1);
    model2 -> setQuery(*qry1);

    for(int i =0;i<=model1->rowCount()-1;i++)
    {
        QString str = model1 -> record(i).value(2).toString() ;
        QString str2 = model2 -> record(i).value(3).toString() ;
        qDebug()<<str<<str2;

        QLabel *lab1 = new QLabel("Food Name : "+str+".");
        QLabel *lab2 = new QLabel("Time and date : "+str2+".");
        frame[i] = new QFrame(this);
        frame[i]->setFrameShape(QFrame::HLine);
        frame[i]->setStyleSheet("background-color:white;");
        lab1->setStyleSheet("background:transprent;Text-align:left;font-family:century gothic;font-size:18px;color:orange;");
        lab2->setStyleSheet("background:transprent;Text-align:left;font-family:century gothic;font-size:15px;color:white;");

        lay->addWidget(lab1);
        lay->addWidget(lab2);
        lay->addWidget(frame[i]);

    }
    ui->scrollAreaWidgetContents->setLayout(lay);
}

void profile::on_pushButton_4_confirm_in_update_clicked()
{
    QString id,name,mobile_number,password,address;
    int nimur;
    QSqlQuery query,query2;

    mobile_number = ui->lineEdit_4_mobile->text();
    password = ui->lineEdit_5_password->text();
    name = ui->lineEdit_3_name->text();
    address = ui->textEdit_2_address->toPlainText();

    if(name.isEmpty() && password.isEmpty() && mobile_number.isEmpty() && address.isEmpty())
    {
        QMessageBox::warning(this,"Fill data","please fill up some information.");
        return;
    }

    if(f==1)
    {
        query.exec("select ID FROM customer_login_info where Mobile_num='"+mobiles+"'");
        if(query.next())
        {
            id = query.value("ID").toString();
            nimur = id.toInt();
            qDebug()<<nimur;
            qDebug()<<id;
        }
        if(!mobile_number.isEmpty()){
            qDebug()<<query2.exec("update customer_login_info SET Mobile_num='"+mobile_number+"' where ID='"+id+"'");
        }

        if(!password.isEmpty()){
            qDebug()<<query2.exec("update customer_login_info SET Password='"+password+"' where ID='"+id+"'");
        }
        if(!name.isEmpty()){
            qDebug()<<query2.exec("update customer_login_info SET Name='"+name+"' where ID='"+id+"'");
        }
        if(!address.isEmpty()){
            qDebug()<<query2.exec("update customer_login_info SET Address='"+address+"' where ID='"+id+"'");
        }
        QMessageBox::information(this,"Update","Your information has been updated.");

    }
    else if(f==2){
        query.exec("select ID FROM vendor_login_info where Mobile_num='"+mobiles+"'");
        if(query.next())
        {
            id = query.value("ID").toString();
            nimur = id.toInt();
            qDebug()<<nimur;
            qDebug()<<id;
        }

        if(!mobile_number.isEmpty()){
              qDebug()<<query2.exec("update vendor_login_info SET Mobile_num='"+mobile_number+"' where ID='"+id+"'");
        }

        if(!password.isEmpty()){
            qDebug()<<query2.exec("update vendor_login_info SET Password='"+password+"' where ID='"+id+"'");
        }
        if(!name.isEmpty()){
            qDebug()<<query2.exec("update vendor_login_info SET Restaurent='"+name+"' where ID='"+id+"'");
        }
        if(!address.isEmpty()){
            qDebug()<<query2.exec("update vendor_login_info SET Address='"+address+"' where ID='"+id+"'");
        }
        QMessageBox::information(this,"Update","Your information has been updated.");
    }

}



void profile::on_pushButton_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    show_profile();
}

void profile::on_pushButton_2_update_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void profile::on_pushButton_3_return_clicked()
{
    if(f==1){
        this->hide();
        prodb.close();
        prodb.removeDatabase(QSqlDatabase::defaultConnection);
        rcustomer = new customers(this,mobiles,f);
        rcustomer  -> show();
    }
    else if(f==2){
        this->hide();
        prodb.close();
        prodb.removeDatabase(QSqlDatabase::defaultConnection);
        rvendor = new vendors(this,mobiles,f);
        rvendor  -> show();
    }
}
