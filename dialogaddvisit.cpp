#include "dialogaddvisit.h"
#include "ui_dialogaddvisit.h"

DialogAddVisit::DialogAddVisit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddVisit)
{
    ui->setupUi(this);
}

DialogAddVisit::~DialogAddVisit()
{
    delete ui;
}
