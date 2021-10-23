#include "dialogdbconnectionconfigure.h"
#include "ui_dialogdbconnectionconfigure.h"

DialogDBConnectionConfigure::DialogDBConnectionConfigure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDBConnectionConfigure)
{
    ui->setupUi(this);
}

DialogDBConnectionConfigure::~DialogDBConnectionConfigure()
{
    delete ui;
}
