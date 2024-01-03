/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open_Database;
    QAction *action_Close;
    QAction *action;
    QAction *actionE_xit;
    QAction *action_Save;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonPrev;
    QPushButton *buttonNext;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *labelSID;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *nameLabel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *labelPHONE;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        action_Open_Database = new QAction(MainWindow);
        action_Open_Database->setObjectName("action_Open_Database");
        action_Close = new QAction(MainWindow);
        action_Close->setObjectName("action_Close");
        action = new QAction(MainWindow);
        action->setObjectName("action");
        actionE_xit = new QAction(MainWindow);
        actionE_xit->setObjectName("actionE_xit");
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName("action_Save");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        buttonPrev = new QPushButton(centralwidget);
        buttonPrev->setObjectName("buttonPrev");

        horizontalLayout->addWidget(buttonPrev);

        buttonNext = new QPushButton(centralwidget);
        buttonNext->setObjectName("buttonNext");

        horizontalLayout->addWidget(buttonNext);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, 8, -1, 8);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        labelSID = new QLabel(centralwidget);
        labelSID->setObjectName("labelSID");

        horizontalLayout_2->addWidget(labelSID);


        horizontalLayout_5->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        nameLabel = new QLabel(centralwidget);
        nameLabel->setObjectName("nameLabel");

        horizontalLayout_3->addWidget(nameLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        horizontalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout_4->addWidget(label_2);

        labelPHONE = new QLabel(centralwidget);
        labelPHONE->setObjectName("labelPHONE");

        horizontalLayout_4->addWidget(labelPHONE);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(horizontalLayout_5);

        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setFrameShape(QFrame::WinPanel);
        tableWidget->setFrameShadow(QFrame::Raised);
        tableWidget->setLineWidth(1);
        tableWidget->setMidLineWidth(1);
        tableWidget->setRowCount(3);
        tableWidget->setColumnCount(2);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setStretchLastSection(false);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 37));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName("menu_File");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Open_Database);
        menu_File->addAction(action_Save);
        menu_File->addAction(action_Close);
        menu_File->addSeparator();
        menu_File->addAction(actionE_xit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_Open_Database->setText(QCoreApplication::translate("MainWindow", "&Open Database", nullptr));
        action_Close->setText(QCoreApplication::translate("MainWindow", "&Close", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        actionE_xit->setText(QCoreApplication::translate("MainWindow", "E&xit", nullptr));
        action_Save->setText(QCoreApplication::translate("MainWindow", "&Save", nullptr));
        buttonPrev->setText(QCoreApplication::translate("MainWindow", "<<", nullptr));
        buttonNext->setText(QCoreApplication::translate("MainWindow", ">>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Student ID:", nullptr));
        labelSID->setText(QCoreApplication::translate("MainWindow", "00000", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Name:", nullptr));
        nameLabel->setText(QCoreApplication::translate("MainWindow", "Foo Bar", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Phone:", nullptr));
        labelPHONE->setText(QCoreApplication::translate("MainWindow", "00-11-222333", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = tableWidget->item(0, 0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "COMP1000", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->item(0, 1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "99.4", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->item(1, 0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "COMP1099", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(1, 1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "50.0", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(2, 0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "COMP1100", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(2, 1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "60.0", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        menu_File->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
