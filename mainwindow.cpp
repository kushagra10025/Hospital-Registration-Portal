#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "exportdbdata.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pix = new QPixmap(":/assets/assets/img/logo.png");
    int w = ui->lbl_logo->width();
    int h = ui->lbl_logo->height();
    ui->lbl_logo->setPixmap(pix->scaled(w,h,Qt::KeepAspectRatio));

    conn = std::make_shared<DBConnection>();
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
    QMessageBox::information(this,"Contact","Contact at (+91)79807-16954 for issues or help!");
}


void MainWindow::on_actionAdd_Patient_triggered()
{
    ui->multi_tabs->setCurrentIndex(0);
}


void MainWindow::on_actionSearch_Patient_triggered()
{
    ui->multi_tabs->setCurrentIndex(1);
}

void MainWindow::on_actionConfigure_Connection_triggered()
{
    std::unique_ptr<DialogDBConnectionConfigure> configureDBDialog = std::make_unique<DialogDBConnectionConfigure>();

//    connect(configureDBDialog, SIGNAL(signalReady(), this, SLOT(someslotfunctionhere())));
    configureDBDialog->setWindowTitle("Configure Database Connection!");
    configureDBDialog->exec();
}


void MainWindow::on_actionExport_DB_as_Excel_triggered()
{
    ExportDBData edb(conn);
    QVector<QString> queries;
    QVector<QString> headers;
    QVector<QString> filenames;
    QString path = "E:/OtherProjects/hhc_files/";

    queries.push_back("select p.reg_no, p.p_fullname,p.p_gender,p.p_pno,p.p_address,p.p_age,p.p_regdate,v.visit_id ,v.date_of_visit,d.doctor_name,v.consultation_fees ,v.consultation_mode ,v.payment_method,v.payment_status,v.payment_date,v.remarks from patient_info p left join visit_details v on p.reg_no = v.reg_no left join doctor_info d on v.doctor_id = d.doctor_id");
    queries.push_back("select * from patient_info");
    queries.push_back("select * from visit_details");
    queries.push_back("select * from doctor_info");

    headers.push_back("Reg No.; Full Name; Gender; Phone No. ; Address ; Age; Reg Date; Visit ID; Visit Date; Doctor Name; Consultation Fees; Consultation Mode; Payment Method; Payment Stauts; Payment Data; Remarks");
    headers.push_back("Reg No.; Full Name; Gender; Phone No. ; Address ; Age; Reg Date");
    headers.push_back("Visit ID; Reg No.; Visit Date; Doctor ID; Consultation Fees ; Consultation Mode; Payment Mode; Payment Status; Payment Date; Remarks");
    headers.push_back("Doctor Id; Doctor Name");

    filenames.push_back("HHC_United.csv");
    filenames.push_back("HHC_PatientInfo.csv");
    filenames.push_back("HHC_VisitDetails.csv");
    filenames.push_back("HHC_DoctorInfo.csv");

    for(int i = 0; i < queries.size(); i++){
        edb.QueryToCSV(queries[i],headers[i],filenames[i],path);
    }
}

