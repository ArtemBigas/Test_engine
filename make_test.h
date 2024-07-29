#ifndef MAKE_TEST_H
#define MAKE_TEST_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include "dialog.h"

namespace Ui {
class make_test;
}

class make_test : public QWidget
{
    Q_OBJECT

public:
    explicit make_test(QWidget *parent = nullptr);
    ~make_test();
    std::vector<QLabel *>labels_q;
    std::vector<QLineEdit *>lineEdits_q;
    std::vector<std::vector<QLabel *>>labels_a;
    std::vector<QLabel *>label_ans;//промежуточный массив для labels_a
    std::vector<std::vector<QLineEdit *>>lineEdits_a;
    std::vector<QLineEdit *>lineEdit_ans;
    std::vector<std::vector<QCheckBox *>>checks_a;
    std::vector<QCheckBox *>check_ans;
signals:
    void MainWindowRequested();

private slots:
    void on_return_menu_button_clicked();

    void on_create_test_button_clicked();

    void on_save_Button_clicked();

private:
    Ui::make_test *ui;
    int num;//количество вопросов


};

#endif // MAKE_TEST_H
