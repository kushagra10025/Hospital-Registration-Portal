#include "addpatient.h"
#include "ui_addpatient.h"

AddPatient::AddPatient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPatient)
{
    ui->setupUi(this);

    conn = new DBConnection();

    qDebug() << conn->get_conn_status() << "From Add Patient";

    // Clear the Form On Start
    on_btn_clear_clicked();
}

AddPatient::~AddPatient()
{
    conn->conn_close();
    delete ui;
}

QString AddPatient::GetUniqueRegistration(QDate date)
{
    QString result = "";
    QString dateStr = "";
    dateStr.append(QString::number((date.year()%100)));
    dateStr.append(QString::number(date.month()));
    dateStr.append(QString::number(date.day()));

    QString hcIdentifier = "/HHC/";
    result.append(dateStr);
    result.append(hcIdentifier);

    QUuid uuid = QUuid::createUuid();
    QString uuidStr = uuid.toString();
    uuidStr = uuidStr.toUpper();
    uuidStr = uuidStr.mid(2,4);
    result.append(uuidStr);

    //TODO Check the Result Generated Now against RegIDs in DB

    return result;
}

void AddPatient::on_btn_register_clicked()
{
    QChar gender = 'O';
    QDate regDate = ui->date_regdate->date();
    qDebug() << regDate.toString();
    QString fullname = ui->txt_fullname->toPlainText();
    QString phone = ui->txt_pno->toPlainText();
    QString address = ui->txt_address->toPlainText();
    QString age = ui->txt_age->toPlainText();
    QString reg_no = GetUniqueRegistration(regDate);

    if(ui->rb_male->isChecked()){
        gender = 'M';
    }else if(ui->rb_female->isChecked()){
        gender = 'F';
    }

    if(fullname.isEmpty() || phone.isEmpty() || address.isEmpty() || age.isEmpty() || reg_no.isEmpty()){
        QMessageBox::information(this,"Empty Field!","Please enter some value!!");
        return;
    }

    if(!conn->get_conn_status()){
        return;
    }

    // TODO Check if Phone No. Already exists and give a warning for continue
    // If No then cancel
    // else add row but make sure Name is different

    QString queryBase = "insert into patient_info(reg_no,p_fullname,p_gender,p_pno,p_address,p_age,p_regdate) values ('"+reg_no+"','"+fullname+"','"+gender+"','"+phone+"','"+address+"','"+age+"','"+regDate.toString()+"')";
    QSqlQuery* qry = new QSqlQuery(conn->get_myDB());
    qry->prepare(queryBase);
    // DO ERROR CHECKING FOR SQL RULES BEFORE EMITTING SIGNAL
    if(qry->exec()){
        QMessageBox::information(this,"Success!","Inserted Successfully!");
    }else{
        QMessageBox::information(this,"Error!","Failed to insert!");
    }

    ui->lbl_gen_reg_no->setText("## "+reg_no);
}


void AddPatient::on_btn_clear_clicked()
{
    ui->date_regdate->setDate(QDate::currentDate());
    ui->txt_fullname->clear();
    ui->txt_age->clear();
    ui->txt_address->clear();
    ui->txt_pno->clear();
    ui->rb_male->setChecked(true);
    ui->lbl_gen_reg_no->setText("## Waiting for Action!");
}

