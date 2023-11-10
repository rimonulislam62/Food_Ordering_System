#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <login_signup_window.h>
#include <QDebug>
#include <QMessageBox>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:



private slots:
    void on_pushButton_2_customer_clicked();

    void on_pushButton_vendor_clicked();

private:
    Ui::MainWindow *ui;
    login_signup_window *log_up;

};
#endif // MAINWINDOW_H
