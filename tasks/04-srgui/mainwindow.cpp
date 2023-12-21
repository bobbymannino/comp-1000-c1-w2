#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Open_Database_triggered()
{
    QString selectedFilePath = QFileDialog::getOpenFileName(this, tr("Open Database"), QDir::homePath(), tr("Database Files (*.txt)"));

    QFile file(selectedFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString fileContents = in.readAll();
        file.close();

        ui->nameLabel->setText(fileContents);
    } else {
        QMessageBox::information(nullptr, "Alert", "Failed to open file");
    }
}
