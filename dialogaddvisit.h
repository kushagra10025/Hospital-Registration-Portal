#ifndef DIALOGADDVISIT_H
#define DIALOGADDVISIT_H

#include <QDialog>
#include <QUuid>
#include <QDate>
#include <QMessageBox>

#include "dbconnection.h"
#include "PROG_ENUMS.h"
#include "printvisit.h"

namespace Ui {
class DialogAddVisit;
}

class DialogAddVisit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddVisit(QSqlRecord* patientRow,std::shared_ptr<DBConnection> conn, QWidget *parent = nullptr);
    ~DialogAddVisit();

signals:
    void printVisitReady(OPDVisitReceiptDetails visitDetails);

private slots:

    void on_btn_clear_clicked();

    void on_btn_add_visit_clicked();

private:
    Ui::DialogAddVisit *ui;

    std::shared_ptr<DBConnection> conn;


    QString p_reg_no;
    QSqlRecord *patientRow;

    QString GetUniqueVisitId(QDate date);

    void setup_dialog_box();
    void add_enums_to_combo_boxes();

    OPDVisitReceiptDetails visitReceiptDetails;
};

#endif // DIALOGADDVISIT_H
