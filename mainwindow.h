#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>

#include "dbconnection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionContact_triggered();

    void on_actionAdd_Patient_triggered();

    void on_actionSearch_Patient_triggered();

private:
    Ui::MainWindow *ui;

    QPixmap* pix;
};
#endif // MAINWINDOW_H
