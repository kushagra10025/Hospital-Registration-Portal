#include "searchpatient.h"
#include "ui_searchpatient.h"

#include <QMenu>


SearchPatient::SearchPatient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPatient)
{
    ui->setupUi(this);

//    conn = new DBConnection();
    conn = std::make_shared<DBConnection>();

    qDebug() << conn->get_conn_status() << "From Search Patients";

    // Clear the form on Start
    on_btn_clear_clicked();

    // Set Default Behaviors
    // ui->tbv_results->setSelectionBehavior(QAbstractItemView::SelectRows);
}

SearchPatient::~SearchPatient()
{
    delete ui;
}

void SearchPatient::on_btn_clear_clicked()
{
    ui->rb_rno->setChecked(true);
    on_rb_rno_clicked();
    ui->txt_in->clear();
    ui->tbv_results->setModel(nullptr);
}


void SearchPatient::on_btn_search_clicked()
{
    QString in;
    in = ui->txt_in->toPlainText();

    if(in.isEmpty() && (ui->rb_pno->isChecked() || ui->rb_rno->isChecked())){
        QMessageBox::information(this,"Empty Field!","Please enter some value!!");
        return;
    }

    if(!conn->get_conn_status()){
        return;
    }

//    QString queryBase = "select * from patient_info";
//    if(ui->rb_rno->isChecked()){
//        queryBase = queryBase + " where reg_no = '"+in+"'";
//    }else if(ui->rb_pno->isChecked()){
//        queryBase = queryBase + " where p_pno = '"+in+"'";
//    }
//    QSqlQueryModel* modal = new QSqlQueryModel();
//    QSqlQuery* qry = new QSqlQuery(conn->get_myDB());
//    qry->prepare(queryBase);
//    qry->exec();
//    modal->setQuery(queryBase);
//    ui->tbv_results->setModel(modal);

    modelDevice = new QSqlTableModel();
    modelDevice->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelDevice->setTable("patient_info");
    if(ui->rb_rno->isChecked()){
        modelDevice->setFilter("reg_no='"+in+"'");
    }else if(ui->rb_pno->isChecked()){
        modelDevice->setFilter("p_pno='"+in+"'");
    }
    modelDevice->select();
    ui->tbv_results->setModel(modelDevice);

    slotUpdateTableModel();

//    qDebug() << modal->rowCount();
}


void SearchPatient::on_rb_showall_clicked()
{
    ui->lbl_in->setText("### Showing All!");
    ui->txt_in->setEnabled(false);
}


void SearchPatient::on_rb_pno_clicked()
{
    ui->lbl_in->setText("### Phone No.");
    ui->txt_in->setEnabled(true);
}


void SearchPatient::on_rb_rno_clicked()
{
    ui->lbl_in->setText("### Registration No.");
    ui->txt_in->setEnabled(true);
}

void SearchPatient::on_tbv_results_customContextMenuRequested(const QPoint &pos)
{
    QMenu * menu = new QMenu(this);

    /* Create actions to the context menu */
    QAction * editDevice = new QAction("Edit Record", this);
    QAction * deleteDevice = new QAction("Delete Record", this);
    QAction * viewVisitsDevice = new QAction("View All Visits/Payments", this);
    QAction * addVisitDevice = new QAction("Add Visit/Payments", this);

    /* Connect slot handlers for Action pop-up menu */
    connect(editDevice, SIGNAL(triggered()), this, SLOT(slotEditRecord()));     // Call Handler dialog editing
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(slotDeleteRecord())); // Handler delete records
    connect(viewVisitsDevice, SIGNAL(triggered()), this, SLOT(slotViewVisits()));
    connect(addVisitDevice, SIGNAL(triggered()), this, SLOT(slotAddVisit()));

    /* Set the actions to the menu */

    menu->addAction(addVisitDevice);
    menu->addAction(viewVisitsDevice);
    menu->addSeparator();
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);
    /* Call the context menu */
    menu->popup(ui->tbv_results->viewport()->mapToGlobal(pos));
}

void SearchPatient::slotEditRecord()
{
    // Ref : https://evileg.com/en/post/71/
    // Ref : https://evileg.com/en/post/76/

    DialogEditPatient *addEditDialog = new DialogEditPatient(&rowCurrentlyBeingEdited);

    connect(addEditDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateEditTableModel()));

    addEditDialog->setWindowTitle("Edit Patient Data!");
    addEditDialog->exec();
}

void SearchPatient::slotDeleteRecord()
{
    int row = ui->tbv_results->selectionModel()->currentIndex().row();

    if(row >= 0){
        if(QMessageBox::warning(this, "Confirm Deletion?","Are you sure you want to delete the selected patient record?",QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
            qDebug() << "delete cancelled!";
            // DO DB ROLLBACK and RETURN
            return;
        }else{
            qDebug() << "deleted successfully!";
            if(!modelDevice->removeRow(row)){
                QMessageBox::warning(this,"Notification","Could not delete entry \nMaybe it is being used by other tables \nCheck all dependencies and try again");
            }
            modelDevice->select();
            ui->tbv_results->setCurrentIndex(modelDevice->index(-1, -1));;
        }
    }
}

void SearchPatient::slotUpdateTableModel()
{
    // Config Table View
    modelDevice->select();
    ui->tbv_results->resizeColumnsToContents();
    ui->tbv_results->horizontalHeader()->setStretchLastSection(true);
    ui->tbv_results->verticalHeader()->setStretchLastSection(true);
}

void SearchPatient::slotUpdateEditTableModel()
{
    qDebug() << "Called from Dialog!";
    modelDevice->setRecord(rowCurrentlySelected,rowCurrentlyBeingEdited);
    on_btn_search_clicked();
}

void SearchPatient::slotViewVisits()
{
    DialogViewVisits *viewVisitsDialog = new DialogViewVisits(&rowCurrentlyBeingEdited, conn);

//    connect(viewVisitsDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateEditTableModel()));

    viewVisitsDialog->setWindowTitle("View Patient Visits/Payment History!");
    viewVisitsDialog->exec();
}

void SearchPatient::slotAddVisit()
{
    qDebug() << "Adding A Visit!";
    DialogAddVisit *addVisitDialog = new DialogAddVisit(&rowCurrentlyBeingEdited, conn);

    // connect(viewVisitsDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateEditTableModel()));
    // TODO Receive the print_confirmation and Record
    // from AddVisit and View Vist and then print the receipt.

    addVisitDialog->setWindowTitle("Add Patient Visit/Payment!");
    addVisitDialog->exec();
}

void SearchPatient::on_tbv_results_clicked(const QModelIndex &index)
{
    rowCurrentlySelected = index.row();
    rowCurrentlyBeingEdited = modelDevice->record(rowCurrentlySelected);

    qDebug() << rowCurrentlySelected;
}

