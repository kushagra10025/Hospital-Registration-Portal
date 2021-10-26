#include "printvisit.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextDocument>

PrintVisit::PrintVisit()
{

}

void PrintVisit::VisitReceiptPDF(OPDVisitReceiptDetails receiptDetails)
{
    qDebug() << receiptDetails.doctorName;
    // TODO Add a variable path to save the PDFs
    // If temp path then delete the file after printing

    QString html_template = "";
    QFile file("E:/OtherProjects/hhc_files/template.html");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Info", file.errorString());
    }else{
        QTextStream in(&file);

        html_template = in.readAll();
    }

    QPdfWriter writer("E:/OtherProjects/hhc_files/test1.pdf");
    writer.setPageSize(QPageSize::A5);
    writer.setResolution(300);
    writer.setPageOrientation(QPageLayout::Landscape);
    writer.setPageMargins(QMargins(2,2,2,2));

    QPainter painter(&writer);
    painter.drawImage(0,-25,QImage(":/assets/assets/template/visit_receipt_template.png"));

    painter.end();
//    QPen pen;
//    pen.setColor(Qt::black);
//    pen.setWidth(5);
//    painter.setPen(pen);

//    QFont font = painter.font();
//    font.setPixelSize(20);
//    font.setUnderline(true);
//    painter.setFont(font);
}
