#include "dialogaddvisit.h"
#include "ui_dialogaddvisit.h"

DialogAddVisit::DialogAddVisit(QSqlRecord* patientRow,std::shared_ptr<DBConnection> conn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddVisit)
{
    ui->setupUi(this);

    this->conn = conn;
    printv = std::make_shared<PrintVisit>();

//    SET FIXED SIZE (NON RESIZEABLE)
//    this->setFixedSize(this->width(),this->height());

    this->patientRow = patientRow;

    add_enums_to_combo_boxes();
    setup_dialog_box();

    p_reg_no = patientRow->value("reg_no").toString();

    QString markdownHeaderDoubleHash = "## ";
    ui->lbl_txt_reg_no->setText(markdownHeaderDoubleHash + p_reg_no);
    ui->lbl_txt_name->setText(markdownHeaderDoubleHash + (patientRow->value("p_fullname").toString()));
}

DialogAddVisit::~DialogAddVisit()
{
    delete ui;
}


QString DialogAddVisit::GetUniqueVisitId(QDate date)
{
    QString result = "";
    QString dateStr = "";
    dateStr.append(QString::number((date.year()%100)));
    dateStr.append(QString::number(date.month()));
    dateStr.append(QString::number(date.day()));

    QString hcIdentifier = "/HHC_V/";
    result.append(dateStr);
    result.append(hcIdentifier);

    QUuid uuid = QUuid::createUuid();
    QString uuidStr = uuid.toString();
    uuidStr = uuidStr.toUpper();
    uuidStr = uuidStr.mid(2,4);
    result.append(uuidStr);

    //TODO Check the Result Generated Now against VisitIDs in DB

    return result;
}

void DialogAddVisit::setup_dialog_box()
{
    ui->date_payment_date->setDate(QDate::currentDate());
    ui->date_visit_date->setDate(QDate::currentDate());

    ui->txt_con_fees->setText("500.00");

    ui->txt_remarks->setText("None");

    ui->combo_consultation_mode->setCurrentIndex(0);
    ui->combo_doctor_name->setCurrentIndex(0);
    ui->combo_payment_method->setCurrentIndex(0);
    ui->combo_payment_status->setCurrentIndex(0);
}

void DialogAddVisit::add_enums_to_combo_boxes()
{
    // GET THE ENUMS AS STRINGS AND ADD TO COMBOBOX
    QStringList list;
    // FOR PAYMENT METHOD
    for(int i = 0;i < PAYMENT_METHOD::PM_C; i++){
        PAYMENT_METHOD pm = static_cast<PAYMENT_METHOD>(i);
        list << PaymentMethod().getValueForKey(pm);
    }
    ui->combo_payment_method->addItems(list);
    ui->combo_payment_method->setCurrentIndex(0);

    list.clear();
    // FOR PAYMENT STATUS
    for(int i = 0;i < PAYMENT_STATUS::PS_C; i++){
        PAYMENT_STATUS ps = static_cast<PAYMENT_STATUS>(i);
        list << PaymentStatus().getValueForKey(ps);
    }
    ui->combo_payment_status->addItems(list);
    ui->combo_payment_status->setCurrentIndex(0);

    list.clear();
    // FOR CONSULTATION STATUS
    for(int i = 0;i < CONSULTATION_MODE::CM_C; i++){
        CONSULTATION_MODE cm = static_cast<CONSULTATION_MODE>(i);
        list << ConsultationMode().getValueForKey(cm);
    }
    ui->combo_consultation_mode->addItems(list);
    ui->combo_consultation_mode->setCurrentIndex(0);

    list.clear();
    // FOR DOCTOR NAMES
    // TODO ADD DOCTOR NAMES TO LIST
    list << "Dr.ABC XYZ" << "Dr.PQR STU" << "Dr.EFG HIJ";
    ui->combo_doctor_name->addItems(list);
    ui->combo_doctor_name->setCurrentIndex(0);

    list.clear();
}

void DialogAddVisit::on_btn_clear_clicked()
{
    setup_dialog_box();
}


void DialogAddVisit::on_btn_add_visit_clicked()
{
    QDate visitDate = ui->date_visit_date->date();
    QString uniqueVisitID = GetUniqueVisitId(visitDate);
    QString visitDateStr = visitDate.toString();
    QString remarksText = ui->txt_remarks->toPlainText();

    QString consulFees = ui->txt_con_fees->toPlainText();
    QString consulMode = ui->combo_consultation_mode->currentText();

    QString paymentDateStr = ui->date_payment_date->date().toString();
    QString paymentMode = ui->combo_payment_method->currentText();
    QString paymentStatus = ui->combo_payment_status->currentText();

    // Get Doctor Id from DoctorName
    // TODO Replace Doctor Name with Doctor Id
    QString doctorName = ui->combo_doctor_name->currentText();

    if(uniqueVisitID.isEmpty() || consulFees.isEmpty() || consulMode.isEmpty() || paymentMode.isEmpty() || paymentStatus.isEmpty() || doctorName.isEmpty()){
        QMessageBox::information(this,"Empty Field!","Please enter some value!!");
        return;
    }

    if(!conn->get_conn_status()){
        return;
    }

    // TODO Perform some checks

    QString queryBase = "insert into visit_details values('"+uniqueVisitID+"','"+p_reg_no+"','"+visitDateStr+"','"+doctorName+"','"+consulFees+"','"+consulMode+"','"+paymentMode+"','"+paymentStatus+"','"+paymentDateStr+"','"+remarksText+"')";
    QSqlQuery* qry = new QSqlQuery(conn->get_myDB());
    qry->prepare(queryBase);
    // DO ERROR CHECKING FOR SQL RULES BEFORE EMITTING SIGNAL
    if(qry->exec()){
        QMessageBox::information(this,"Success!","Inserted Successfully!");
    }else{
        QMessageBox::information(this,"Error!","Failed to insert!");
    }

    qDebug() << "Successfully Inserted Visit!";

    // TODO Go To Print Receipt
    QMessageBox::StandardButton printQues = QMessageBox::question(this,"Print Visit!","Do You want to Print the Visit Details?", QMessageBox::Yes | QMessageBox::No);
    if(printQues == QMessageBox::Yes){
        qDebug() << "Yes Clicked!";
        printv->VisitReceiptPDF(visitReceiptDetails);
    }
    // Auto Clear form After Added the visit!
}

