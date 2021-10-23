#include "dialogviewvisits.h"
#include "ui_dialogviewvisits.h"

DialogViewVisits::DialogViewVisits(QSqlRecord *patientRow, std::shared_ptr<DBConnection> conn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogViewVisits)
{
    ui->setupUi(this);

    this->conn = conn;
    qDebug() << conn->get_conn_status() << "From Dialog View Visits";

    this->patientRow = patientRow;
    QString markdownHeaderDoubleHash = "## ";
    ui->lbl_txt_reg_no->setText(markdownHeaderDoubleHash + (patientRow->value("reg_no").toString()));
    ui->lbl_txt_name->setText(markdownHeaderDoubleHash + (patientRow->value("p_fullname").toString()));
}

DialogViewVisits::~DialogViewVisits()
{
    delete ui;
}
