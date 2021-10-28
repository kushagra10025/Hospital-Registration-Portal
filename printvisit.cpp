#include "printvisit.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextDocument>
#include <QUuid>
//#include <QPrinter>
//#include <QPrintDialog>

PrintVisit::PrintVisit()
{
    one = { "", "One ", "Two ", "Three ", "Four ",
                     "Five ", "Six ", "Seven ", "eight ",
                     "Nine ", "Ten ", "Eleven ", "Twelve ",
                     "Thirteen ", "Fourteen ", "Fifteen ",
                     "Sixteen ", "Seventeen ", "Eighteen ",
                     "Nineteen " };

    ten = { "", "", "Twenty ", "Thirty ", "Forty ",
                     "Fifty ", "Sixty ", "Seventy ", "Eighty ",
                     "Ninety " };
}

QString PrintVisit::NumberToWords(int n, QString s)
{
    QString str = "";
    if (n > 19)
        str += ten[n / 10] + one[n % 10];
    else
        str += one[n];

    if (n)
        str += s;

    return str;
}

QString PrintVisit::ConvertToWords(QString str)
{
    bool ok;

    long n = str.toLong(&ok, 10);
    QString out;

    out += NumberToWords((n / 10000000), "Crore ");
    out += NumberToWords(((n / 100000) % 100), "Lakh ");
    out += NumberToWords(((n / 1000) % 100), "Thousand ");
    out += NumberToWords(((n / 100) % 10), "Hundred ");

    if (n > 100 && n % 100)
        out += "and ";

    out += NumberToWords((n % 100), "");

    return out;
}

void PrintVisit::VisitReceiptPDF(OPDVisitReceiptDetails receiptDetails)
{
    qDebug() << receiptDetails.doctorName;
    // TODO Add a variable path to save the PDFs
    // If temp path then delete the file after printing

    QString filePath = "E:/OtherProjects/hhc_files/";
    QString fileName = "";
    QUuid uuid = QUuid::createUuid();
    fileName.append(uuid.toString());
    fileName.append(".pdf");

    filePath.append(fileName);

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize::A5);
    writer.setResolution(300);
    writer.setPageOrientation(QPageLayout::Landscape);
    writer.setPageMargins(QMargins(2,2,2,2));

    QPainter painter(&writer);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(5);
    painter.setPen(pen);

    QFont font = painter.font();
    font.setPixelSize(38);
    painter.setFont(font);

    painter.drawImage(0,-25,QImage(":/assets/assets/template/visit_receipt_template.png"));
    painter.drawText(450,605, receiptDetails.visitId);
    painter.drawText(1700,605, receiptDetails.patientRegNo);
    painter.drawText(650,685, receiptDetails.consulMode);
    painter.drawText(1875,685, receiptDetails.doctorName);
    painter.drawText(600,755, receiptDetails.paymentStatus);
    painter.drawText(1200,755, receiptDetails.paymentMode);
    painter.drawText(1650,755, receiptDetails.additionalRemarks);
    painter.drawText(560,892, receiptDetails.patientName);
    painter.drawText(1250,892, receiptDetails.patientAge);
    painter.drawText(1550,892, receiptDetails.patientGender);
    painter.drawText(1900,892, receiptDetails.patientVisitDate);
    painter.drawText(450,958, receiptDetails.patientAddress);
    painter.drawText(1600,958, receiptDetails.patientPhone);
    painter.drawText(1675,1150, receiptDetails.cosulFees);
    painter.drawText(250,1150, receiptDetails.particulars);
    QString rsfront = "Rs. ";
    rsfront.append(ConvertToWords(receiptDetails.cosulFees));
    rsfront.append("only.");
    painter.drawText(625,1430, rsfront);
    painter.end();

    // Actual Printing through Printer happens here!
    // Currently use the Default PDF Viewer to handle printing of the PDFs
        // QPrinter printer;
        // printer.setPrinterName("Desired Printer Name");
        // QPrintDialog dialog(&printer);
        // if(dialog.exec() == QDialog::Rejected) return;

    // Open in Default PDF Viewer and Use that to print
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));

}
