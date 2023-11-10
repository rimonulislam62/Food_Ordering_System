#include "vendors.h"
#include "ui_vendors.h"
#include "login_signup_window.h"
#include<QSqlDatabase>
#include <QScrollArea>
#include <QFileDialog>

login_signup_window *d;
QString imagepath;
int t=0;
QScrollArea *scrollarea[10];


vendors::vendors(QWidget *parent, QString mobile_num,int x) :
    QMainWindow(parent),
    ui(new Ui::vendors)
{
    ui->setupUi(this);
    mobile = mobile_num;
    z=x;
    ui->stackedWidget->setCurrentIndex(0);

}

vendors::~vendors()
{
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
    delete ui;
}

//database opening
void vendors::Database_open()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/New folder/online-food-ordering-system-in-QT-main/online_food_ordering_system/online_food_ordering_system/resources/online_food_ordering_system.db");
    if(db.open())
        qDebug()<<"DataBase Connected...";
    else
        qDebug()<<"DataBase Failed to Connect...";
}


//changing page to ADD Food page
void vendors::on_pushButton_add_Food_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    Database_open();
}

//changing page to remove food page
void vendors::on_pushButton_2_remove_food_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    Database_open();
    Scroll_Area();

}

//selecting image for food
void vendors::on_pushButton_add_photo_clicked()
{
    imagepath = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
    QPixmap pic = QPixmap(imagepath);
    //qDebug()<<imagePath;
    ui->label_add_photo_in_addfood->setPixmap(pic);
    ui->label_add_photo_in_addfood->setScaledContents(true);

}


//adding food to database
void vendors::on_pushButton_add_food_clicked()
{

    qDebug()<<db.isOpen();
    QString FoodTitle,description,price;
    FoodTitle=ui->lineEdit_title->text();
    description=ui->textEdit_description->toPlainText();
    price=ui->lineEdit_3_price->text();

    if(FoodTitle.isEmpty() || description.isEmpty() || price.isEmpty())
    {
        QMessageBox::warning(this,"Fill all data","please fill up all the information.");
        return;
    }
    QSqlQuery qry;
    qry.prepare("insert into FoodData(FoodItem,Description,Price,Photo,Mobile_no)"
                "values(?,?,?,?,?)");
    qDebug()<< FoodTitle<<description<<price<<imagepath<<mobile;

    qry.addBindValue(FoodTitle);
    qry.addBindValue(description);
    qry.addBindValue(price);
    qry.addBindValue(imagepath);
    qry.addBindValue(mobile);

    if(qry.exec())
    {
        qDebug()<<"Data inserted";
        QMessageBox::about(this,"Food Add","Your new item has been added!");
    }
    else
        qDebug()<<"Data not inserted";

    ui->lineEdit_title->clear();
    ui->textEdit_description->clear();
    ui->lineEdit_3_price->clear();
    ui->stackedWidget->setCurrentIndex(0);
    ui->label_add_photo_in_addfood->clear();
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
    Database_open();
}


//showing related food of vendor's from database to remove
void vendors::Scroll_Area()
{
    scrollarea[t] = new QScrollArea(this);
    scrollarea[t]->setGeometry(0,40,238,431);
    scrollarea[t]->setStyleSheet("background-color:black;");
    QPushButton *name[100];

    QSqlQueryModel *model1 = new QSqlQueryModel();
    //QSqlQueryModel *model2 = new QSqlQueryModel();
    QSqlQueryModel *model3 = new QSqlQueryModel();

    QSqlQuery *qry1 = new QSqlQuery(db);
    //QSqlQuery *qry2 = new QSqlQuery(mydb);
    QSqlQuery *qry3 = new QSqlQuery(db);
   // qry1 -> prepare("select FoodItem from FoodData");

    qDebug()<<qry1->exec("select FoodItem from FoodData where Mobile_no='"+mobile+"'");
    //qDebug()<<qry2->exec("select Description from FoodData");
    qDebug()<<qry3->exec("select Price from FoodData where Mobile_no='"+mobile+"'");

    model1 -> setQuery(*qry1);
    //model2 -> setQuery(*qry2);
    model3 -> setQuery(*qry3);
    QVBoxLayout *lay=new QVBoxLayout(this);
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
        lay-> addWidget(frame[i]);

         connect(name[i],SIGNAL(clicked()),this,SLOT(onnameclicked()));


    }
    scrollarea[t]->setLayout(lay);
    //scrollarea[t]->setWidgetResizable(true);
    scrollarea[t]->show();
    ui ->frame->hide();

}

QString ButtonText;
int vendors::y=0 ;
QPushButton *PButton[100];

//to activate frame which show Food details
void vendors::onnameclicked()
{

    ui->frame->show();

    PButton[y] = new QPushButton;
    PButton[y] = qobject_cast<QPushButton*>(sender());

    if(y>0)
    {
        PButton[y-1]->setObjectName("btnName_1");
        PButton[y-1] ->setStyleSheet("QPushButton#btnName_1{background:transprent;Text-align:left;font-family:century gothic;font-size:18px;color:orange;}"
                                     "QPushButton#btnName_1:hover{color:yellow;font-size:22px;}");
    }

    PButton[y] ->setStyleSheet("Text-align:left;font-family:century gothic;font-size:18px;color:yellow;");

    ButtonText=PButton[y]->text();

    ui->label_3_name->setText(ButtonText);
     Database_open();

    QSqlQuery qry10;
    qDebug()<<qry10.exec("select * from FoodData where FoodItem='"+ButtonText+"'");

    while(qry10.next()){

            QPixmap propic;
            QString loc=qry10.value(4).toString();
            propic.load(loc);

            ui->label_2_pic->setPixmap(propic);
            ui->label_2_pic->setScaledContents(true);
            ui->textEdit_description_in_page3->setPlainText(""+qry10.value(2).toString()+".");
              y++;
              db.close();
              db.removeDatabase(QSqlDatabase::defaultConnection);

        }

}

//to remove food from database
void vendors::on_pushButton_remove_food_clicked()
{
    Database_open();
    QSqlQuery qry;
    qDebug()<<qry.exec("DELETE FROM FoodData where FoodItem='"+ButtonText+"'");
    ui->stackedWidget->setCurrentIndex(0);
    scrollarea[t]->close();
    t++;
}

void vendors::on_pushButton_return_button_in_page2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void vendors::on_pushButton_return_button_in_page3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    scrollarea[t]->close();
}

//logout button for vendor
void vendors::on_pushButton_logout_in_page1_clicked()
{
    this->hide();
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
    d = new login_signup_window(this,2);
    d->show();
}




void vendors::on_pushButton_vendor_profile_clicked()
{
    this->hide();
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
    proV = new profile(this,mobile,z);
    proV->show();
}
