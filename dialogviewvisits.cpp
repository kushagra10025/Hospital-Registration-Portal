#include "dialogviewvisits.h"
#include "ui_dialogviewvisits.h"

DialogViewVisits::DialogViewVisits(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogViewVisits)
{
    ui->setupUi(this);
}

DialogViewVisits::~DialogViewVisits()
{
    delete ui;
}
