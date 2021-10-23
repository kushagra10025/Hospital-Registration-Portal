#ifndef DIALOGVIEWVISITS_H
#define DIALOGVIEWVISITS_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>

#include "dbconnection.h"

namespace Ui {
class DialogViewVisits;
}

class DialogViewVisits : public QDialog
{
    Q_OBJECT

public:
    explicit DialogViewVisits(QSqlRecord *patientRow, std::shared_ptr<DBConnection> conn, QWidget *parent = nullptr);
    ~DialogViewVisits();

private slots:
    void slotUpdateTableModel();

private:
    Ui::DialogViewVisits *ui;

    std::shared_ptr<DBConnection> conn;

    QString p_reg_no;
    QSqlRecord *patientRow;

    QSqlTableModel* modelVisit;

    QString GetUniqueVisitId(QDate date);
    void FillTableWithDetails();

public:
    QString getRegNo();
};

#endif // DIALOGVIEWVISITS_H
