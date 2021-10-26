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

    p_reg_no = patientRow->value("reg_no").toString();

    QString markdownHeaderDoubleHash = "## ";
    ui->lbl_txt_reg_no->setText(markdownHeaderDoubleHash + p_reg_no);
    ui->lbl_txt_name->setText(markdownHeaderDoubleHash + (patientRow->value("p_fullname").toString()));

    FillTableWithDetails();
}

DialogViewVisits::~DialogViewVisits()
{
    delete ui;
}

void DialogViewVisits::slotUpdateTableModel()
{
    modelVisit->select();

    ui->tbv_view_visits->resizeColumnsToContents();
    ui->tbv_view_visits->horizontalHeader()->setStretchLastSection(true);
    ui->tbv_view_visits->verticalHeader()->setStretchLastSection(true);
}

void DialogViewVisits::slotPrintVisitDetails()
{
    qDebug() << "Printing Current Visit!";
    qDebug() << rowCurrentlyBeingEdited.field(1).value();
}

void DialogViewVisits::FillTableWithDetails()
{
    if(!conn->get_conn_status()){
        qDebug() << "Connection Failed!";
        return;
    }

    modelVisit = new QSqlTableModel();
    modelVisit->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelVisit->setTable("visit_details");
    // TODO: Display Selected Columns with different names
    modelVisit->setFilter("reg_no='"+p_reg_no+"'");
    modelVisit->select();

    ui->tbv_view_visits->setModel(modelVisit);

    slotUpdateTableModel();
}

void DialogViewVisits::on_tbv_view_visits_customContextMenuRequested(const QPoint &pos)
{
    QMenu* menu = new QMenu(this);

    /* Create actions to the context menu */
    QAction * printVisit = new QAction("Print Visit Details!",this);

    /* Connect slot handler for Action pop-up menu */
    // TODO Add Print Slot
    connect(printVisit, SIGNAL(triggered()),this, SLOT(slotPrintVisitDetails()));

    /* Set the actions to the menu */
    menu->addAction(printVisit);

    /* Call the context menu */
    menu->popup(ui->tbv_view_visits->viewport()->mapToGlobal(pos));
}


void DialogViewVisits::on_tbv_view_visits_clicked(const QModelIndex &index)
{
    rowCurrentlySelected = index.row();
    rowCurrentlyBeingEdited = modelVisit->record(rowCurrentlySelected);

    qDebug() << rowCurrentlySelected;
}

