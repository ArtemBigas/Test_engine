#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QApplication>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void setMainWindow();//переключает на главное меню
    void setmake_test();//переключает на меню создания теста
    void setchange_test();//переключает на меню изменения теста
     void setabout_test();//переключает на меню about
    Ui::Dialog *ui;
};

#endif // DIALOG_H
