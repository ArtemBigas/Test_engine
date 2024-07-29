#include "about_test.h"
#include "ui_about_test.h"

about_test::about_test(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::about_test)
{
    ui->setupUi(this);
}

about_test::~about_test()
{
    delete ui;
}

void about_test::on_returnButton_clicked()
{
    emit MainWindowRequested();
}

