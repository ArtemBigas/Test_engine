#include "dialog.h"
//#include "make_test.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog mainwindow;
    mainwindow.setWindowTitle("Test editor");
    mainwindow.setWindowFlags(mainwindow.windowFlags() | Qt::WindowMaximizeButtonHint);
    mainwindow.show();
    return a.exec();
}
