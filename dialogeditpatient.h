#ifndef DIALOGEDITPATIENT_H
#define DIALOGEDITPATIENT_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDebug>

#include <vector>

namespace Ui {
class DialogEditPatient;
}

class DialogEditPatient : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditPatient(QSqlRecord *rowEdit, QWidget *parent = nullptr);
    ~DialogEditPatient();

signals:
    void signalReady();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_update_clicked();

private:
    Ui::DialogEditPatient *ui;

    QString p_reg_no;
    QSqlRecord *rowToEdit;

public:
    QString getRegNo();
};

#endif // DIALOGEDITPATIENT_H
