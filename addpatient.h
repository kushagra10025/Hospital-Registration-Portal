#ifndef ADDPATIENT_H
#define ADDPATIENT_H

#include <QWidget>
#include <QDebug>
#include <QDate>
#include <QUuid>
#include <QMessageBox>

#include "dbconnection.h"

namespace Ui {
class AddPatient;
}

class AddPatient : public QWidget
{
    Q_OBJECT

public:
    explicit AddPatient(QWidget *parent = nullptr);
    ~AddPatient();

private slots:
    void on_btn_register_clicked();

    void on_btn_clear_clicked();

private:
    Ui::AddPatient *ui;

    DBConnection* conn;

    QString GetUniqueRegistration(QDate date);
};

#endif // ADDPATIENT_H
