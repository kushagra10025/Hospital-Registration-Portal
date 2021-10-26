#ifndef PRINTVISIT_H
#define PRINTVISIT_H

#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QSqlRecord>

struct OPDReceiptDetails{
    QString patientName;
    QString patientAge;
    QString patientGender;
    QString patientAddress;
    QString patientPhone;
};

struct OPDVisitReceiptDetails : OPDReceiptDetails{
    QString patientVisitDate;
    QString visitId;

    // Get Doctor Id from DoctorName
    // TODO Replace Doctor Name with Doctor Id
    QString doctorName;

    QString cosulFees;
    QString consulMode;

    QString paymentMode;
    QString paymentStatus;
    QString paymentDate;

    QString particulars;

    QString totalAmount;

    QString amountInWords;

    QString additionalRemarks;
};

class PrintVisit
{
public:
    PrintVisit();

    void VisitReceiptPDF(OPDVisitReceiptDetails receiptDetails);
};

#endif // PRINTVISIT_H
