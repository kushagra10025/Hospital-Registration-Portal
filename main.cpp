#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Hathidah Health Care");
    QCoreApplication::setOrganizationDomain("com.hhc");
    QCoreApplication::setApplicationName("HHC Main Desk Portal");

    MainWindow w;
    w.show();
    return a.exec();
}
