#ifndef DIALOGVIEWVISITS_H
#define DIALOGVIEWVISITS_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlRecord>
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

private:
    Ui::DialogViewVisits *ui;

    std::shared_ptr<DBConnection> conn;

    QString p_reg_no;
    QSqlRecord *patientRow;

public:
    QString getRegNo();
};

#endif // DIALOGVIEWVISITS_H
