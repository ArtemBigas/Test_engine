#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void make_testRequested();
    void change_testRequested();
    void about_testRequested();

private slots:

    void on_exit_button_clicked();

    void on_make_test_button_clicked();

    void on_change_test_button_clicked();

    void on_about_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
