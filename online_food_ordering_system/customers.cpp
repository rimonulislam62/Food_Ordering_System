#include "customers.h"
#include "ui_customers.h"
#include "QLabel"
#include "QFrame"
#include "QDateTime"
#include <QMessageBox>
#include <login_signup_window.h>

login_signup_window *b;

customers::customers(QWidget *parent, QString mobile_num,int f) :
    QMainWindow(parent),
    ui(new Ui::customers)
{
    ui->setupUi(this);
    mobile=mobile_num;
    k = f;
    Database_open();
    Scroll_Area();
}

customers::~customers()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
    delete ui;
}

//for opening database
void customers::Database_open()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("D:/New folder/online-food-ordering-system-in-QT-main/online_food_ordering_system/online_food_ordering_system/resources/online_food_ordering_system.db");
    if(mydb.open())
    {
        qDebug()<<"open!";
    }
    else
    {
        qDebug()<<"fail to open!!";
    }

}


//data insertion from database in scroll area
void customers::Scroll_Area()
{

    QPushButton *name[100];

    QSqlQueryModel *model1 = new QSqlQueryModel();
    //QSqlQueryModel *model2 = new QSqlQueryModel();
    QSqlQueryModel *model3 = new QSqlQueryModel();

    QSqlQuery *qry1 = new QSqlQuery(mydb);
    //QSqlQuery *qry2 = new QSqlQuery(mydb);
    QSqlQuery *qry3 = new QSqlQuery(mydb);
   // qry1 -> prepare("select FoodItem from FoodData");

    qDebug()<<qry1->exec("select FoodItem from FoodData");
    //qDebug()<<qry2->exec("select Description from FoodData");
    qDebug()<<qry3->exec("select Price from FoodData");

    model1 -> setQuery(*qry1);
    //model2 -> setQuery(*qry2);
    model3 -> setQuery(*qry3);
    QVBoxLayout *lay = new QVBoxLayout(this);
    QFrame *frame[20];

    for(int i =0;i<=model1->rowCount()-1;i++)
    {
        QString str = model1 -> record(i).value(0).toString() ;
        //QString str1 = model2 -> record(i).value(0).toString() ;
        QString str2 = model3 -> record(i).value(0).toString() ;


        name[i]= new QPushButton(str);
        name[i] ->setObjectName("btnName_1");
        name[i] -> setStyleSheet("QPushButton#btnName_1{background:transprent;Text-align:left;font-family:century gothic;font-size:18px;color:orange;}"
                                "QPushButton#btnName_1:hover{color:yellow;font-size:22px;}");

       // QLabel *lab = new QLabel("Describtion : "+str1+"\nPrize : "+str2+".");
        QLabel *lab = new QLabel("Prize : "+str2+".");
        frame[i] = new QFrame(this);
        frame[i]->setFrameShape(QFrame::HLine);
        frame[i]->setStyleSheet("background-color:white;");

        lab ->setStyleSheet("background:transprent;Text-align:left;font-family:century gothic;font-size:18px;color:white;");

        lay->addWidget(name[i]);
        lay -> addWidget(lab);
        lay -> addWidget(frame[i]);

         connect(name[i],SIGNAL(clicked()),this,SLOT(onnameclicked()));

    }



    ui->scrollAreaWidgetContents->setLayout(lay);
    ui ->frame->hide();
}

QString buttonText;
int customers::x=0 ;
QPushButton *pButton[100];

//this function is for connection food name button to frame
void customers::onnameclicked()
{

    ui->frame->show();

    pButton[x] = new QPushButton;
    pButton[x] = qobject_cast<QPushButton*>(sender());

    if(x>0)
    {
        pButton[x-1]->setObjectName("btnName_1");
        pButton[x-1] ->setStyleSheet("QPushButton#btnName_1{background:transprent;Text-align:left;font-family:century gothic;font-size:18px;color:orange;}"
                                     "QPushButton#btnName_1:hover{color:yellow;font-size:22px;}");
    }

    pButton[x] ->setStyleSheet("Text-align:left;font-family:century gothic;font-size:18px;color:yellow;");

    buttonText=pButton[x]->text();

    ui->label_3_Food_name->setText(buttonText);

    Database_open();
    QSqlQuery qry;
    qDebug()<<qry.exec("select * from FoodData where FoodItem='"+buttonText+"'");

    while(qry.next()){

            QPixmap propic;
            QString loc=qry.value(4).toString();
            propic.load(loc);

            ui->label_2_pic->setPixmap(propic);
            ui->label_2_pic->setScaledContents(true);
            ui->textEdit_in_customer_page->setPlainText("Description :"+qry.value(2).toString()+".");
              x++;
            mydb.close();
            mydb.removeDatabase(QSqlDatabase::defaultConnection);

        }

}

//this is for placing order and for history
void customers::on_pushButton_order_place_clicked()
{
    Database_open();
    QDateTime timestamp = QDateTime::currentDateTime();
    QSqlQuery qry;
    qry.prepare("INSERT INTO History(Mobile_num,FoodItem,TimeDate)"
             "VALUES(?,?,?);");
    qry.addBindValue(mobile);
    qry.addBindValue(buttonText);

    QString time = timestamp.toString("yyyy-MM-dd hh:mm:ss");
    qDebug()<<time;
    qry.addBindValue(time);
    if(qry.exec()){
        QMessageBox::information(this,"Order","Your Order has Confirmed!");
    }

}

//this is for loging out
void customers::on_pushButton_log_out_clicked()
{
    this->hide();
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
    b = new login_signup_window(this,1);
    b->show();
}



void customers::on_pushButton_2_profile_clicked()
{
    this->hide();
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
    pro = new profile(this,mobile,k);
    pro->show();
}
