#include "dialogeditpatient.h"
#include "ui_dialogeditpatient.h"



DialogEditPatient::DialogEditPatient(QSqlRecord *rowEdit, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditPatient)
{
    ui->setupUi(this);

    rowToEdit = rowEdit;
    ui->txt_fullname->setText(rowToEdit->value("p_fullname").toString());
    ui->txt_pno->setText(rowToEdit->value("p_pno").toString());
    ui->txt_address->setText(rowToEdit->value("p_address").toString());
    ui->txt_age->setText(rowToEdit->value("p_age").toString());
    if(rowToEdit->value("p_gender").toString() == "M"){
        ui->rb_male->setChecked(true);
    }else if(rowToEdit->value("p_gender").toString() == "F"){
        ui->rb_female->setChecked(true);
    }
    ui->date_regdate->setDate(QDate::fromString(rowToEdit->value("p_regdate").toString()));
    ui->lbl_gen_reg_no->setText(rowToEdit->value("reg_no").toString());
}

DialogEditPatient::~DialogEditPatient()
{
    delete ui;
}

void DialogEditPatient::on_btn_cancel_clicked()
{
    this->close();
}


void DialogEditPatient::on_btn_update_clicked()
{
    std::vector<QString> inputs(rowToEdit->count());
    inputs[0] = ui->lbl_gen_reg_no->text();
    inputs[1] = ui->txt_fullname->toPlainText();
    if(ui->rb_male->isChecked()){
        inputs[2] = "M";
    }else if(ui->rb_female->isChecked()){
        inputs[2] = "F";
    }
    inputs[3] = ui->txt_pno->toPlainText();
    inputs[4] = ui->txt_address->toPlainText();
    inputs[5] = ui->txt_age->toPlainText();
    inputs[6] = ui->date_regdate->date().toString();

    if(inputs[0].isEmpty() || inputs[1].isEmpty() || inputs[2].isEmpty() || inputs[3].isEmpty() || inputs[4].isEmpty() || inputs[5].isEmpty() || inputs[6].isEmpty()){
        QMessageBox::information(this,"Empty Field!","Please enter some value!!");
        return;
    }

    int cols = rowToEdit->count();
    for(int i = 0;i<cols;i++){
        rowToEdit->setValue(i,inputs[i]);
    }

    // DO ERROR CHECKING FOR SQL RULES BEFORE EMITTING SIGNAL
    emit signalReady();
    this->close();
}

QString DialogEditPatient::getRegNo()
{
    return p_reg_no;
}
