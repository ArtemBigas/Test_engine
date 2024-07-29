#ifndef ABOUT_TEST_H
#define ABOUT_TEST_H

#include <QWidget>

namespace Ui {
class about_test;
}

class about_test : public QWidget
{
    Q_OBJECT

public:
    explicit about_test(QWidget *parent = nullptr);
    ~about_test();
signals:
    void MainWindowRequested();
private slots:
    void on_returnButton_clicked();

private:
    Ui::about_test *ui;
};

#endif // ABOUT_TEST_H
