#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_exit_button_clicked()
{
    qApp->exit();
}


void MainWindow::on_make_test_button_clicked()
{
    emit make_testRequested();
}


void MainWindow::on_change_test_button_clicked()
{
    emit change_testRequested();
}

void MainWindow::on_about_button_clicked()
{
    emit about_testRequested();
}

