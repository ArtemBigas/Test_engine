#include "make_test.h"
#include "ui_make_test.h"
#include <QScrollArea>
#include <QTextStream>
#include <QFile>
#include <QDir>
make_test::make_test(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::make_test)
{
    ui->setupUi(this);
}

make_test::~make_test()
{
    delete ui;
}

void make_test::on_return_menu_button_clicked()
{
    emit MainWindowRequested();
}


void make_test::on_create_test_button_clicked()
{
    num = ui->spinBox->value(); // количество вопросов

    QVBoxLayout *layout = new QVBoxLayout;//создаем пустой контейнер
    QWidget *widget = new QWidget;//создаем пустой виджет
    QLabel *instruction = new QLabel("Please mark the correct answer (there can only be one) on the right.");
    instruction->setFont(QFont("Purisa", 12));
    layout->addWidget(instruction);
    for (int i = 0; i < num; ++i)
    {
        QLabel *label_q = new QLabel(QString("Question %1").arg(i+1));
        labels_q.push_back(label_q);
        QLineEdit *lineEdit_q = new QLineEdit;
        lineEdits_q.push_back(lineEdit_q);
        QHBoxLayout *hLayout_q = new QHBoxLayout;//чтобы lineEdit_q был справа от label_q
        hLayout_q->addWidget(label_q);//добавляем виджет label_q в  контейнер hLayout_q
        hLayout_q->addWidget(lineEdit_q);//текст
        layout->addLayout(hLayout_q);//добавляем контейнер в контейнер

        for (int j = 0; j < 3; ++j)
        {
            QLabel *label_a = new QLabel(QString("Variant %1").arg(j+1));
            label_ans.push_back(label_a);
            QLineEdit *lineEdit_a = new QLineEdit;
            lineEdit_ans.push_back(lineEdit_a);
            QCheckBox *check_a=new QCheckBox;
             check_ans.push_back(check_a);
            QHBoxLayout *hLayout_a = new QHBoxLayout;
            hLayout_a->addWidget(label_a);//добавляем виджет label_q в  контейнер hLayout_q
            hLayout_a->addWidget(lineEdit_a);
            hLayout_a->addWidget(check_a);
            layout->addLayout(hLayout_a);//добавляем контейнер в контейнер
        }
        labels_a.push_back(label_ans);
        lineEdits_a.push_back(lineEdit_ans);
        checks_a.push_back(check_ans);
        label_ans.clear();
        lineEdit_ans.clear();
        check_ans.clear();
    }

    widget->setLayout(layout);//делаем из контейнера layout отдельный виджет
    ui->scrollArea->setWidget(widget);//вставляем в scrollArea виджет widget
}



void make_test::on_save_Button_clicked()
{
   QTextStream out(stdout);
    //QCoreApplication::applicationDirPath() возвращает путь к директории, в которой находится исполняемый файл.
    QString filename = QCoreApplication::applicationDirPath() + "/tests/" + ui->Title_Edit->text() + ".txt";
   // Убедимся, что директория tests существует, если нет - создаем ее
   QDir dir(QCoreApplication::applicationDirPath() + "/tests");
   if (!dir.exists()) {
       dir.mkpath(".");
   }
     QFile test(filename);// Создаем объект
    if (test.open(QIODevice::WriteOnly)) {
        QTextStream out(&test); // поток записываемых данных направляем в файл

        for (int i = 0; i < num; ++i) {
            out << labels_q[i]->text() << "_" << lineEdits_q[i]->text() << endl;

            for (int j = 0; j < 3; ++j) {
                out << labels_a[i][j]->text() << "_" << lineEdits_a[i][j]->text() << "_";
                if(!checks_a[i][j]->isChecked())// флажок не установлен
                {
                    out <<"wrong"<< endl;
                }
                else
                {
                    out <<"true"<< endl;
                };
            }
        }
    } else {
        qWarning("Could not open file");
    }
}




