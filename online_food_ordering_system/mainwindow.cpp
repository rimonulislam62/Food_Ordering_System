#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete log_up;

}


//this is mainwindow push button's work:
//this is vendor button's work:
void MainWindow::on_pushButton_vendor_clicked()
{

    hide();
    int x=2;
    log_up = new login_signup_window(this,x);
    log_up->show();
}

//this is customer button's work:
void MainWindow::on_pushButton_2_customer_clicked()
{

    hide();
    int x = 1;
    log_up = new login_signup_window(this,x);
    log_up->show();
}

