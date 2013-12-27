#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Register synchronous event(SINGAL & SLOT) to close MainWindow
    //by menubar
    QObject::connect(ui->actionExitByMenuBar,SIGNAL(triggered()),this,SLOT(close()));
    //by toolbutton
    QObject::connect(ui->actionExitByToolBar,SIGNAL(triggered()),this,SLOT(close()));

    //open FileDialog
    QObject::connect(ui->actionOpenByMenuBar,SIGNAL(triggered()),this,SLOT(OnOpenFileButtonClicked()));
    QObject::connect(ui->actionOpenFolderByToolBar,SIGNAL(triggered()),this,SLOT(OnOpenFileButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
//SLOT : When Click OpenFolder Action Control,it will have a slot OnOpenFileButtonClicked() and go here.
void MainWindow::OnOpenFileButtonClicked(){
    QString PathDestination = "graphical_Modeling_system_GUI/GMS XML Files";
    QDir fileDir(QDir::currentPath());
    fileDir.cd("../" + PathDestination);
    fileName = QFileDialog::getOpenFileName(this,tr("Open GMS XML File"),
                                            fileDir.path(),tr("XML Files (*.xml)"));

}
