#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "encodejson.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::output()
{
    QString a = "d";
    qDebug() << a;

}

