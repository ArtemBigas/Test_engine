#include "change_test.h"
#include "ui_change_test.h"
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QMessageBox>
change_test::change_test(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::change_test)
{//перед каждым запуском надо почистить все вектора, если пользователь не захочет сохранять прогресс
    labels_qc.clear();
    lineEdits_qc.clear();
    labels_ac.clear();
    label_ansc.clear();
    lineEdits_ac.clear();
    lineEdit_ansc.clear();
    checks_ac.clear();
    check_ansc.clear();
    ui->setupUi(this);
}

change_test::~change_test()
{
    delete ui;
}


void change_test::on_open_Button_clicked()
{
   QTextStream out(stdout);
    //QCoreApplication::applicationDirPath() возвращает путь к директории, в которой находится исполняемый файл.
    QString filename = QCoreApplication::applicationDirPath() + "/tests/" + ui->Title_Edit->text()+ ".txt";
   QFile test(filename);// Создаем объект
    // Убедимся, что директория tests существует, если нет - ошибка
    QDir dir(QCoreApplication::applicationDirPath() + "/tests");
    if (!dir.exists()) {
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("There is not folder <<tests>>."));
    };
    if(!test.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("Cannot open file for reading"));
    }
    else
    {    QVBoxLayout *layout = new QVBoxLayout;//создаем пустой контейнер
        QWidget *widget = new QWidget;//создаем пустой виджет
    // Создаем входящий поток, из которого будут считываться данные, и связываем его с нашим файлом
        QTextStream in(&test);
        numc=0;//счетчик вопросов
       while (!in.atEnd())
        {   QString line = in.readLine();// метод readLine() считывает одну строку из потока, без него цикл бесконечный
            QLabel *label_qc = new QLabel(QString("Question %1").arg(numc+1));
            labels_qc.push_back(label_qc);
            numc++;
            QLineEdit *lineEdit_qc = new QLineEdit;
             QStringList parts = line.split("_"); // Разделение строки по пробелу
             QString line1 = parts[1];
             lineEdit_qc->setText(line1);//вставляем текст
            lineEdits_qc.push_back(lineEdit_qc);
            QHBoxLayout *hLayout_qc = new QHBoxLayout;//чтобы lineEdit_q был справа от label_q
            hLayout_qc->addWidget(label_qc);//добавляем виджет label_q в  контейнер hLayout_q
            hLayout_qc->addWidget(lineEdit_qc);//текст
            layout->addLayout(hLayout_qc);//добавляем контейнер в контейнер

            for (int j = 0; j < 3; ++j)
            {   line = in.readLine();
                QLabel *label_ac = new QLabel(QString("Variant %1").arg(j+1));
                label_ansc.push_back(label_ac);
                QLineEdit *lineEdit_ac = new QLineEdit;
                QStringList parts = line.split("_"); // Разделение строки по пробелу
                QString line1 = parts[1];
                lineEdit_ac->setText(line1);//вставляем текст
                lineEdit_ansc.push_back(lineEdit_ac);
                QCheckBox *check_ac=new QCheckBox;
                QString line2 = parts[2];
                if(line2=="true"){check_ac->setChecked(true);};
                check_ansc.push_back(check_ac);
                QHBoxLayout *hLayout_ac = new QHBoxLayout;
                hLayout_ac->addWidget(label_ac);//добавляем виджет label_q в  контейнер hLayout_q
                hLayout_ac->addWidget(lineEdit_ac);
                hLayout_ac->addWidget(check_ac);
                layout->addLayout(hLayout_ac);//добавляем контейнер в контейнер
            }
            labels_ac.push_back(label_ansc);
            lineEdits_ac.push_back(lineEdit_ansc);
            checks_ac.push_back(check_ansc);
            label_ansc.clear();
            lineEdit_ansc.clear();
            check_ansc.clear();
        }
       widget->setLayout(layout);//делаем из контейнера layout отдельный виджет
       ui->scrollArea->setWidget(widget);//вставляем в scrollArea виджет widget
    }
    // Закрываем файл
    test.close();
}


void change_test::on_save_Button_clicked()
{   QTextStream out(stdout);
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

        for (int i = 0; i < numc; ++i) {
            out << labels_qc[i]->text() << "_" << lineEdits_qc[i]->text() << endl;

            for (int j = 0; j < 3; ++j) {
                out << labels_ac[i][j]->text() << "_" << lineEdits_ac[i][j]->text() << "_";
                if(!checks_ac[i][j]->isChecked())// флажок не установлен
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


void change_test::on_return_menu_Button_clicked()
{
    emit MainWindowRequested();
}

void change_test::on_Add_question_clicked()
{
    QTextStream out(stdout);
    //QCoreApplication::applicationDirPath() возвращает путь к директории, в которой находится исполняемый файл.
    QString filename = QCoreApplication::applicationDirPath() + "/tests/" + ui->Title_Edit->text()+ ".txt";
    QFile test(filename);// Создаем объект
    // Убедимся, что директория tests существует, если нет - ошибка
    QDir dir(QCoreApplication::applicationDirPath() + "/tests");
    if (!dir.exists()) {
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("There is not folder <<tests>>."));
    };
    if(!test.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("Cannot open file for reading"));
    }
    else
    {
    int add = ui->spinBox->value();//номер нового вопроса
    if(add<=0 || add>numc+1)
    {
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("Incorrect number"));
    }
    else
    {
        numc++;
//Задача:перерисовать виджет с вопросами и ответами так, чтобы на месте add появился пустой виджет, а также в массивы добавился ещё один пункт
     QLabel *label_qc = new QLabel(QString("Question %1").arg(add));//создаем новый QLabel для вопроса
      labels_qc.insert(labels_qc.begin() + add-1, label_qc);
      QLineEdit *lineEdit_qc = new QLineEdit;
      lineEdits_qc.insert(lineEdits_qc.begin() + add-1, lineEdit_qc);
      for (int j = 0; j < 3; ++j)
      {QLabel *label_ac = new QLabel(QString("Variant %1").arg(j+1));
      label_ansc.push_back(label_ac);
       QLineEdit *lineEdit_ac = new QLineEdit;
       lineEdit_ansc.push_back(lineEdit_ac);
       QCheckBox *check_ac=new QCheckBox;
       check_ansc.push_back(check_ac);
      };
      //записываем варианты ответов в соответствующие массивы и удаляем промежуточные
      labels_ac.insert(labels_ac.begin() + add-1, label_ansc);
      lineEdits_ac.insert(lineEdits_ac.begin() + add-1, lineEdit_ansc);
      checks_ac.insert(checks_ac.begin() + add-1, check_ansc);
      label_ansc.clear();
      lineEdit_ansc.clear();
      check_ansc.clear();
//Теперь необходимо все вывести на экран
      QVBoxLayout *layout = new QVBoxLayout;//создаем пустой контейнер
      QWidget *widget = new QWidget;//создаем пустой виджет
      for (int i = 0; i < numc; ++i)
      {
          if(i+1>=add){labels_qc[i]=new QLabel(QString("Question %1").arg(i+1));
          lineEdits_qc[i];};//номер вопроса и сам вопрос
          QHBoxLayout *hLayout_qc = new QHBoxLayout;//чтобы lineEdit_qc был справа от label_qc
          hLayout_qc->addWidget(labels_qc[i]);//добавляем виджет label_qc в  контейнер hLayout_qc
          hLayout_qc->addWidget(lineEdits_qc[i]);//текст
          layout->addLayout(hLayout_qc);//добавляем контейнер в контейнер


          for (int j = 0; j < 3; ++j)
          {
              QHBoxLayout *hLayout_aс = new QHBoxLayout;
              hLayout_aс->addWidget(labels_ac[i][j]);//добавляем виджет label_q в  контейнер hLayout_q
              hLayout_aс->addWidget(lineEdits_ac[i][j]);
              hLayout_aс->addWidget(checks_ac[i][j]);
              layout->addLayout(hLayout_aс);//добавляем контейнер в контейнер

          }
      }

      widget->setLayout(layout);//делаем из контейнера layout отдельный виджет
      ui->scrollArea->setWidget(widget);//вставляем в scrollArea виджет widget
    };

    }
}


void change_test::on_Delete_question_clicked()
{
    QTextStream out(stdout);
    //QCoreApplication::applicationDirPath() возвращает путь к директории, в которой находится исполняемый файл.
    QString filename = QCoreApplication::applicationDirPath() + "/tests/" + ui->Title_Edit->text()+ ".txt";
    QFile test(filename);// Создаем объект
    // Убедимся, что директория tests существует, если нет - ошибка
    QDir dir(QCoreApplication::applicationDirPath() + "/tests");
    if (!dir.exists()) {
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("There is not folder <<tests>>."));
    };
    if(!test.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("Cannot open file for reading"));
    }
    else
    {
        int del = ui->spinBox_2->value();//номер нового вопроса
        if(del<=0||del>numc)
        {
            QMessageBox::critical(this,
                                  tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                                  tr("Incorrect number"));
        }
        else
        {
         labels_qc.erase(labels_qc.begin() + del-1);
         lineEdits_qc.erase(lineEdits_qc.begin() + del-1);
         labels_ac.erase(labels_ac.begin() + del-1);
         lineEdits_ac.erase(lineEdits_ac.begin() + del-1);
         checks_ac.erase(checks_ac.begin() + del-1);
         numc--;
         //Теперь необходимо все вывести на экран
         QVBoxLayout *layout = new QVBoxLayout;//создаем пустой контейнер
         QWidget *widget = new QWidget;//создаем пустой виджет
         for (int i = 0; i < numc; ++i)
         {
             if(i>=del-1){labels_qc[i]=new QLabel(QString("Question %1").arg(i+1));
                 lineEdits_qc[i];};//номер вопроса и сам вопрос
             QHBoxLayout *hLayout_qc = new QHBoxLayout;//чтобы lineEdit_qc был справа от label_qc
             hLayout_qc->addWidget(labels_qc[i]);//добавляем виджет label_qc в  контейнер hLayout_qc
             hLayout_qc->addWidget(lineEdits_qc[i]);//текст
             layout->addLayout(hLayout_qc);//добавляем контейнер в контейнер


             for (int j = 0; j < 3; ++j)
             {
                 QHBoxLayout *hLayout_aс = new QHBoxLayout;
                 hLayout_aс->addWidget(labels_ac[i][j]);//добавляем виджет label_q в  контейнер hLayout_q
                 hLayout_aс->addWidget(lineEdits_ac[i][j]);
                 hLayout_aс->addWidget(checks_ac[i][j]);
                 layout->addLayout(hLayout_aс);//добавляем контейнер в контейнер

             }
         }

         widget->setLayout(layout);//делаем из контейнера layout отдельный виджет
         ui->scrollArea->setWidget(widget);//вставляем в scrollArea виджет widget

        }
    }

}

