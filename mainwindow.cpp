#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pix = new QPixmap(":/assets/assets/img/logo.png");
    int w = ui->lbl_logo->width();
    int h = ui->lbl_logo->height();
    ui->lbl_logo->setPixmap(pix->scaled(w,h,Qt::KeepAspectRatio));

//    conn = new DBConnection();
//    qDebug() << conn->get_conn_status();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"About","HHC Patient Registration Portal\nv0.0.1\nDeveloped InHouse");
}


void MainWindow::on_actionContact_triggered()
{
    QMessageBox::information(this,"Contact","Contact at (+91)XXXXX-XXXXX for issues or help!");
}


void MainWindow::on_actionAdd_Patient_triggered()
{
    ui->multi_tabs->setCurrentIndex(0);
}


void MainWindow::on_actionSearch_Patient_triggered()
{
    ui->multi_tabs->setCurrentIndex(1);
}
