#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <map>
#include <vector>
#include "gmsModel.h"
#include "xmlErrorCode.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //fileName
    QString fileName;
    GMSModel gmsModel;

private slots:
    //When Click OpenFolder Action Control,it will have a slot OnOpenFileButtonClicked() and go here.
    void OnOpenFileButtonClicked();
};

#endif // MAINWINDOW_H
