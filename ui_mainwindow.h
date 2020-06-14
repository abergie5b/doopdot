/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_Image;
    QAction *actionSave_As;
    QAction *actionSettings;
    QAction *actionSobel;
    QAction *actionPrewitt;
    QAction *actionMedian;
    QAction *actionLaPlacian;
    QAction *actionMaximum;
    QAction *actionMinimum;
    QAction *actionBilinear;
    QAction *actionBicubic;
    QAction *actionResample;
    QAction *actionNearest_Neighbor;
    QAction *actionRotate;
    QAction *actionNegative;
    QAction *actionInvert_Channels;
    QAction *actionTo_Grey;
    QAction *actionContrast_Equalization;
    QAction *actionVisualize;
    QAction *actionDoopDot;
    QAction *actionReset_Image;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frame;
    QWidget *tab_2;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAlgorithms;
    QMenu *menuFilter;
    QMenu *menuResizing;
    QMenu *menuTransform;
    QMenu *menuHistogram;
    QMenu *menuAbout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(919, 772);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionLoad_Image = new QAction(MainWindow);
        actionLoad_Image->setObjectName(QStringLiteral("actionLoad_Image"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        actionSobel = new QAction(MainWindow);
        actionSobel->setObjectName(QStringLiteral("actionSobel"));
        actionPrewitt = new QAction(MainWindow);
        actionPrewitt->setObjectName(QStringLiteral("actionPrewitt"));
        actionMedian = new QAction(MainWindow);
        actionMedian->setObjectName(QStringLiteral("actionMedian"));
        actionLaPlacian = new QAction(MainWindow);
        actionLaPlacian->setObjectName(QStringLiteral("actionLaPlacian"));
        actionMaximum = new QAction(MainWindow);
        actionMaximum->setObjectName(QStringLiteral("actionMaximum"));
        actionMinimum = new QAction(MainWindow);
        actionMinimum->setObjectName(QStringLiteral("actionMinimum"));
        actionBilinear = new QAction(MainWindow);
        actionBilinear->setObjectName(QStringLiteral("actionBilinear"));
        actionBicubic = new QAction(MainWindow);
        actionBicubic->setObjectName(QStringLiteral("actionBicubic"));
        actionResample = new QAction(MainWindow);
        actionResample->setObjectName(QStringLiteral("actionResample"));
        actionNearest_Neighbor = new QAction(MainWindow);
        actionNearest_Neighbor->setObjectName(QStringLiteral("actionNearest_Neighbor"));
        actionRotate = new QAction(MainWindow);
        actionRotate->setObjectName(QStringLiteral("actionRotate"));
        actionNegative = new QAction(MainWindow);
        actionNegative->setObjectName(QStringLiteral("actionNegative"));
        actionInvert_Channels = new QAction(MainWindow);
        actionInvert_Channels->setObjectName(QStringLiteral("actionInvert_Channels"));
        actionTo_Grey = new QAction(MainWindow);
        actionTo_Grey->setObjectName(QStringLiteral("actionTo_Grey"));
        actionContrast_Equalization = new QAction(MainWindow);
        actionContrast_Equalization->setObjectName(QStringLiteral("actionContrast_Equalization"));
        actionVisualize = new QAction(MainWindow);
        actionVisualize->setObjectName(QStringLiteral("actionVisualize"));
        actionDoopDot = new QAction(MainWindow);
        actionDoopDot->setObjectName(QStringLiteral("actionDoopDot"));
        actionReset_Image = new QAction(MainWindow);
        actionReset_Image->setObjectName(QStringLiteral("actionReset_Image"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-color: #EFEFEF; color: black"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        frame = new QFrame(tab);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(-1, -1, 901, 701));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tableWidget = new QTableWidget(tab_2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(-5, 1, 901, 701));
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 919, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAlgorithms = new QMenu(menuBar);
        menuAlgorithms->setObjectName(QStringLiteral("menuAlgorithms"));
        menuFilter = new QMenu(menuAlgorithms);
        menuFilter->setObjectName(QStringLiteral("menuFilter"));
        menuResizing = new QMenu(menuAlgorithms);
        menuResizing->setObjectName(QStringLiteral("menuResizing"));
        menuTransform = new QMenu(menuAlgorithms);
        menuTransform->setObjectName(QStringLiteral("menuTransform"));
        menuHistogram = new QMenu(menuAlgorithms);
        menuHistogram->setObjectName(QStringLiteral("menuHistogram"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAlgorithms->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionReset_Image);
        menuFile->addAction(actionLoad_Image);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionSettings);
        menuAlgorithms->addAction(menuResizing->menuAction());
        menuAlgorithms->addAction(menuFilter->menuAction());
        menuAlgorithms->addAction(menuTransform->menuAction());
        menuAlgorithms->addAction(menuHistogram->menuAction());
        menuFilter->addAction(actionSobel);
        menuFilter->addAction(actionPrewitt);
        menuFilter->addAction(actionMedian);
        menuFilter->addAction(actionLaPlacian);
        menuFilter->addAction(actionMaximum);
        menuFilter->addAction(actionMinimum);
        menuResizing->addAction(actionBilinear);
        menuResizing->addAction(actionBicubic);
        menuResizing->addAction(actionResample);
        menuResizing->addAction(actionNearest_Neighbor);
        menuTransform->addAction(actionRotate);
        menuTransform->addAction(actionNegative);
        menuTransform->addAction(actionInvert_Channels);
        menuTransform->addAction(actionTo_Grey);
        menuHistogram->addAction(actionVisualize);
        menuHistogram->addAction(actionContrast_Equalization);
        menuAbout->addAction(actionDoopDot);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Canny Filter Editor", Q_NULLPTR));
        actionLoad_Image->setText(QApplication::translate("MainWindow", "Load Image", Q_NULLPTR));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As ...", Q_NULLPTR));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
        actionSobel->setText(QApplication::translate("MainWindow", "Sobel", Q_NULLPTR));
        actionPrewitt->setText(QApplication::translate("MainWindow", "Prewitt", Q_NULLPTR));
        actionMedian->setText(QApplication::translate("MainWindow", "Median", Q_NULLPTR));
        actionLaPlacian->setText(QApplication::translate("MainWindow", "LaPlacian", Q_NULLPTR));
        actionMaximum->setText(QApplication::translate("MainWindow", "Maximum", Q_NULLPTR));
        actionMinimum->setText(QApplication::translate("MainWindow", "Minimum", Q_NULLPTR));
        actionBilinear->setText(QApplication::translate("MainWindow", "Bilinear", Q_NULLPTR));
        actionBicubic->setText(QApplication::translate("MainWindow", "Bicubic", Q_NULLPTR));
        actionResample->setText(QApplication::translate("MainWindow", "Resample", Q_NULLPTR));
        actionNearest_Neighbor->setText(QApplication::translate("MainWindow", "Nearest Neighbor", Q_NULLPTR));
        actionRotate->setText(QApplication::translate("MainWindow", "Rotate", Q_NULLPTR));
        actionNegative->setText(QApplication::translate("MainWindow", "Negative", Q_NULLPTR));
        actionInvert_Channels->setText(QApplication::translate("MainWindow", "Invert Channels", Q_NULLPTR));
        actionTo_Grey->setText(QApplication::translate("MainWindow", "To Grey", Q_NULLPTR));
        actionContrast_Equalization->setText(QApplication::translate("MainWindow", "Contrast Equalization", Q_NULLPTR));
        actionVisualize->setText(QApplication::translate("MainWindow", "Show Pixel Distribution", Q_NULLPTR));
        actionDoopDot->setText(QApplication::translate("MainWindow", "DoopDot", Q_NULLPTR));
        actionReset_Image->setText(QApplication::translate("MainWindow", "Reset Image", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Image", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Log", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuAlgorithms->setTitle(QApplication::translate("MainWindow", "Algorithms", Q_NULLPTR));
        menuFilter->setTitle(QApplication::translate("MainWindow", "Kernels", Q_NULLPTR));
        menuResizing->setTitle(QApplication::translate("MainWindow", "Resize", Q_NULLPTR));
        menuTransform->setTitle(QApplication::translate("MainWindow", "Transform", Q_NULLPTR));
        menuHistogram->setTitle(QApplication::translate("MainWindow", "Histogram", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
