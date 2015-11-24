#include <iostream>

#include <fstream>
#include <QFile>
#include <QXmlStreamWriter>
#include <map>
#include <QString>
#include <QDebug>

#include "baseinterface.h"
#include "primSampleDGPP.h"
#include "primBinTreeDGPP.h"

using namespace std;

void create_performance_test (int test_size, QString test_type, QString file_name ) {

    ofstream outp_file(file_name.toStdString().c_str());
    outp_file << test_size << endl;

   if (test_type == QString("SIMPLE")) {
       int pos_value;
       for(int i = 0; i < test_size; i++) {
        for(int j = 0; j < test_size; j++) {
            if (j == i || j == i + 1)
               pos_value = 1;
            else
                pos_value = 0;
             outp_file << pos_value << " ";
        }
        outp_file << endl;

       }
   }
   else if (test_type == QString("RAND")) {
       throw;
   }

   outp_file.close();
}



void run_tests(QXmlStreamWriter& xml, QString file_name) {
    BaseInterface* interface_class;
    double result;

    xml.writeStartElement(file_name);

    // Чтобы тест не расписовать, вот один прекрасный макрос.
#define one_test(x) interface_class = new (x);\
    result = interface_class->run_performance_test(file_name.toStdString());\
    xml.writeTextElement(QString(#x), QString::number(result));\
    delete interface_class


    one_test(PrimaBinTreeDGPP);
    one_test(PrimaSampleDGPP);

    xml.writeEndElement();
}

/*
 *  Аргументы:
 *  0 - имя программы (стандартно)
 *  1 - надо ли выполнять генерацию тестов: 1 - надо, 0 - считаем, что сами тесты сгенерированы
 *  2... - по парно идёт слеудщая информация: на чётных местах размер теста, на нечётных - тип теста
 */
int main(int argc, char** argv)
{
     QFile file_results("results.xml");
     file_results.open(QIODevice::WriteOnly);

     QXmlStreamWriter xml(&file_results);
     xml.setAutoFormatting(true);
     xml.writeStartDocument();

     bool gen_test = (QString(argv[1]) == QString("1") ? true : false);

     for (int argi = 2; argi < argc; argi += 2) {
         int test_n = (argi-2)/2 + 1;
         // Размер теста
         int test_size = QString(argv[argi]).toInt();
         QString test_type = QString(argv[argi+1]);

         qDebug() << "Test " << test_n << ": " << test_size << " " << test_type;

         // Сформируем файл с тестовым графом
        QString test_file = QString("performance_") + test_size + QString("_") + test_type + QString(".txt");
        if (gen_test) {
            qDebug() << "\tCreating test matrix";
            create_performance_test(test_size, test_type, test_file);
        }


     }

     xml.writeEndDocument();
     file_results.close();
     return 0;
}

