#ifndef DIALOGADDVISIT_H
#define DIALOGADDVISIT_H

#include <QDialog>

namespace Ui {
class DialogAddVisit;
}

class DialogAddVisit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddVisit(QWidget *parent = nullptr);
    ~DialogAddVisit();

private:
    Ui::DialogAddVisit *ui;
};

#endif // DIALOGADDVISIT_H
