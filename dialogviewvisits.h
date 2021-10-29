#ifndef DIALOGVIEWVISITS_H
#define DIALOGVIEWVISITS_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QMenu>

#include "dbconnection.h"
#include "printvisit.h"

namespace Ui {
class DialogViewVisits;
}

class DialogViewVisits : public QDialog
{
    Q_OBJECT

public:
    explicit DialogViewVisits(QSqlRecord *patientRow, std::shared_ptr<DBConnection> conn, QWidget *parent = nullptr);
    ~DialogViewVisits();

signals:
    void printVisitReady(OPDVisitReceiptDetails receitVisit);

private slots:
    void slotUpdateTableModel();

    void slotPrintVisitDetails();

    void on_tbv_view_visits_customContextMenuRequested(const QPoint &pos);

    void on_tbv_view_visits_clicked(const QModelIndex &index);

private:
    Ui::DialogViewVisits *ui;

    std::shared_ptr<DBConnection> conn;

    QString p_reg_no;
    QSqlRecord *patientRow;

    QSqlTableModel* modelVisit;
    int rowCurrentlySelected;
    QSqlRecord rowCurrentlyBeingEdited;

    OPDVisitReceiptDetails visitReceiptDetails;

    QString GetDoctorNameFromId(QString ID);
    QString GetUniqueVisitId(QDate date);
    void FillTableWithDetails();

public:
    QString getRegNo();
};

#endif // DIALOGVIEWVISITS_H
