#ifndef CHANGE_TEST_H
#define CHANGE_TEST_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include "dialog.h"

namespace Ui {
class change_test;
}

class change_test : public QWidget
{
    Q_OBJECT

public:
    explicit change_test(QWidget *parent = nullptr);
    ~change_test();
    std::vector<QLabel *>labels_qc;
    std::vector<QLineEdit *>lineEdits_qc;
    std::vector<std::vector<QLabel *>>labels_ac;
    std::vector<QLabel *>label_ansc;//промежуточный массив для labels_ac
    std::vector<std::vector<QLineEdit *>>lineEdits_ac;
    std::vector<QLineEdit *>lineEdit_ansc;
    std::vector<std::vector<QCheckBox *>>checks_ac;
    std::vector<QCheckBox *>check_ansc;


signals:
    void MainWindowRequested();

private slots:


    void on_save_Button_clicked();

    void on_return_menu_Button_clicked();

    void on_open_Button_clicked();

    void on_Add_question_clicked();

    void on_Delete_question_clicked();

private:
    Ui::change_test *ui;
    int numc;//количество вопросов
};

#endif // CHANGE_TEST_H
