#ifndef DIALOGDBCONNECTIONCONFIGURE_H
#define DIALOGDBCONNECTIONCONFIGURE_H

#include <QDialog>

namespace Ui {
class DialogDBConnectionConfigure;
}

class DialogDBConnectionConfigure : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDBConnectionConfigure(QWidget *parent = nullptr);
    ~DialogDBConnectionConfigure();

private:
    Ui::DialogDBConnectionConfigure *ui;
};

#endif // DIALOGDBCONNECTIONCONFIGURE_H
