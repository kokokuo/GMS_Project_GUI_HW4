/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenByMenuBar;
    QAction *actionExitByMenuBar;
    QAction *actionOpenFolderByToolBar;
    QAction *actionExitByToolBar;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        actionOpenByMenuBar = new QAction(MainWindow);
        actionOpenByMenuBar->setObjectName(QStringLiteral("actionOpenByMenuBar"));
        actionExitByMenuBar = new QAction(MainWindow);
        actionExitByMenuBar->setObjectName(QStringLiteral("actionExitByMenuBar"));
        actionOpenFolderByToolBar = new QAction(MainWindow);
        actionOpenFolderByToolBar->setObjectName(QStringLiteral("actionOpenFolderByToolBar"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/toolButton_images/asset images/folder_open_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFolderByToolBar->setIcon(icon);
        actionExitByToolBar = new QAction(MainWindow);
        actionExitByToolBar->setObjectName(QStringLiteral("actionExitByToolBar"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/toolButton_images/asset images/exit_48px.png"), QSize(), QIcon::Normal, QIcon::On);
        actionExitByToolBar->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 431, 241));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpenByMenuBar);
        menuFile->addAction(actionExitByMenuBar);
        mainToolBar->addAction(actionOpenFolderByToolBar);
        mainToolBar->addAction(actionExitByToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpenByMenuBar->setText(QApplication::translate("MainWindow", "Open", 0));
        actionExitByMenuBar->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionOpenFolderByToolBar->setText(QApplication::translate("MainWindow", "Open", 0));
        actionExitByToolBar->setText(QApplication::translate("MainWindow", "Exit", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
