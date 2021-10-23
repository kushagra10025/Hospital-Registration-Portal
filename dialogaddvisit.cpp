#include "dialogaddvisit.h"
#include "ui_dialogaddvisit.h"

DialogAddVisit::DialogAddVisit(QSqlRecord* patientRow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddVisit)
{
    ui->setupUi(this);

//    // SET FIXED SIZE (NON RESIZEABLE)
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
    QString uniqueVisitID = GetUniqueVisitId(ui->date_visit_date->date());
    qDebug() << "Unique Visit ID : " << uniqueVisitID << " for " << p_reg_no;
}

