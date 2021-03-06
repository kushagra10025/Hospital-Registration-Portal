#ifndef SEARCHPATIENT_H
#define SEARCHPATIENT_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>

#include "dbconnection.h"
#include "dialogeditpatient.h"
#include "dialogviewvisits.h"
#include "dialogaddvisit.h"
#include "printvisit.h"

namespace Ui {
class SearchPatient;
}

class SearchPatient : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPatient(QWidget *parent = nullptr);
    ~SearchPatient();

private slots:
    void on_btn_clear_clicked();

    void on_btn_search_clicked();

    void on_rb_showall_clicked();

    void on_rb_pno_clicked();

    void on_rb_rno_clicked();

    void on_tbv_results_customContextMenuRequested(const QPoint &pos);

    void slotEditRecord();

    void slotDeleteRecord();

    void slotUpdateTableModel();

    void slotUpdateEditTableModel();

    void slotViewVisits();

    void slotAddVisit();

    void slotPrintVisit(OPDVisitReceiptDetails receitVisit);

    void on_tbv_results_clicked(const QModelIndex &index);

private:
    Ui::SearchPatient *ui;

    std::shared_ptr<DBConnection> conn;
    std::shared_ptr<PrintVisit> printv;

    QSqlTableModel* modelDevice;
    int rowCurrentlySelected;
    QSqlRecord rowCurrentlyBeingEdited;

    OPDVisitReceiptDetails receitVisit;

};

#endif // SEARCHPATIENT_H
