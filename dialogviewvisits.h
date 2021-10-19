#ifndef DIALOGVIEWVISITS_H
#define DIALOGVIEWVISITS_H

#include <QDialog>

namespace Ui {
class DialogViewVisits;
}

class DialogViewVisits : public QDialog
{
    Q_OBJECT

public:
    explicit DialogViewVisits(QWidget *parent = nullptr);
    ~DialogViewVisits();

private:
    Ui::DialogViewVisits *ui;
};

#endif // DIALOGVIEWVISITS_H
