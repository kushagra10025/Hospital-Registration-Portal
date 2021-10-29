#ifndef PRINTVISIT_H
#define PRINTVISIT_H

#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QSqlRecord>
#include <array>

struct OPDReceiptDetails{
    QString patientRegNo;
    QString patientName;
    QString patientAge;
    QString patientGender;
    QString patientAddress;
    QString patientPhone;
};

struct OPDVisitReceiptDetails : OPDReceiptDetails{
    QString patientVisitDate;
    QString visitId;

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

    QString NumberToWords(int n, QString s);
    QString ConvertToWords(QString str);
    void VisitReceiptPDF(OPDVisitReceiptDetails receiptDetails);
private:
    std::array<QString,20> one;
    std::array<QString,10> ten;
};

#endif // PRINTVISIT_H
