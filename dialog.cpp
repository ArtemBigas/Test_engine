#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->main, &MainWindow::make_testRequested,this, &Dialog::setmake_test);
    connect(ui->main, &MainWindow::change_testRequested,this, &Dialog::setchange_test);
    connect(ui->main, &MainWindow::about_testRequested,this, &Dialog::setabout_test);
    connect(ui->make, &make_test::MainWindowRequested,this, &Dialog::setMainWindow);
    connect(ui->change, &change_test::MainWindowRequested,this, &Dialog::setMainWindow);
    connect(ui->about, &about_test::MainWindowRequested,this, &Dialog::setMainWindow);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setMainWindow()

{
    QWidget* widget = findChild<QWidget*>("main");
    ui->stackedWidget->setCurrentWidget(widget);
}

void Dialog::setmake_test()
{    //ui->stackedWidget->setCurrentWidget(0);
    QWidget* widget = findChild<QWidget*>("make");//ищет виджет по названию
    ui->stackedWidget->setCurrentWidget(widget);
}
void Dialog::setchange_test()
{    //ui->stackedWidget->setCurrentWidget(0);
    QWidget* widget = findChild<QWidget*>("change");//ищет виджет по названию
    ui->stackedWidget->setCurrentWidget(widget);
}
void Dialog::setabout_test()
{    //ui->stackedWidget->setCurrentWidget(0);
    QWidget* widget = findChild<QWidget*>("about");//ищет виджет по названию
    ui->stackedWidget->setCurrentWidget(widget);
}
