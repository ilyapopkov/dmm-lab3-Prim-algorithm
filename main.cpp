#include <iostream>

#include <fstream>
#include <QFile>
#include <QXmlStreamWriter>
#include <map>
#include <QString>
#include <QDebug>

#include "baseinterface.h"

#include "primSimpleDGPP.h"
#include "primBinTreeDGPP.h"
#include "primSimpleVSSS.h"
#include "primBinTreeVSSS.h"
#include "primSimpleVKB.h"
#include "primBinTreeVKB.h"

using namespace std;
// test_size_v - количество узлов
// test_size_e - количество рёбер
void create_performance_test (int test_size_v, int test_size_e, QString test_type, QString file_name ) {

    ofstream outp_file(file_name.toStdString().c_str());
    outp_file << test_size_v << endl;

    int edges_count = 0;

   // В простейшем тесте рёбер всегда 2 * test_size_v, он не интересен
   if (test_type == QString("SIMPLE")) {
       int pos_value;
       for(int i = 0; i < test_size_v; i++) {
        for(int j = 0; j < test_size_v; j++) {
            if (j == i + 1 || j == i-1)
               pos_value = 1;
            else
                pos_value = 0;
             outp_file << pos_value << " ";
        }
        outp_file << endl;

       }
   }
   else if (test_type == QString("RAND") || test_type == QString("FULL")) {
       map<QString, int> values;
       QString key;
       int pos_value;
       int full_e = (test_size_v - 1)* test_size_v / 2;
       int e_i = 0;

       qDebug() << "\t\tGenerating test " << test_size_v << " " << test_size_v;
       for(int i = 0; i < test_size_v; i++) {
           int row_edge_n = 0;
        for(int j = 0; j < test_size_v; j++) {


            int edges_left = full_e - e_i;
            int edges_left_add = test_size_e - edges_count;
            if (i < j)
                e_i++;

            int min_i = std::max(i, j);
            int max_i = std::min(i, j);
           // qDebug() << i << " " << j << "\t\tLeft edges: " << edges_left << " not zero edges " << edges_count;
            if (i == j)
                pos_value = 0;
            else {

                key = QString::number(min_i) + "#" + QString::number(max_i);
                map<QString, int>::iterator el = values.find(key);

                //qDebug() << "\t\tKey" << i << " " << j << " " << key;

                if (el != values.end()) {
                  //  qDebug() << "\t\tExists 1!";
                    pos_value = el->second;
                }
                else {
                    bool add_edge;
                    if(j == test_size_v - 1 && row_edge_n == 0) {
                         add_edge = true;
                       //  qDebug() << "\t\tZero row i = " << i << " j = " << j << " row_count = " << row_edge_n;
                    }
                    else
                        add_edge = (rand()%4 == 0 || edges_left <= edges_left_add) && edges_count <= test_size_e;

                    // qDebug() << "\t\tG Left edges: " << edges_left << " not zero edges " << edges_count << " size: " << test_size_e << " left to build: " << edges_left_add;
                     if (add_edge)  {
                         pos_value = rand()%15 + 1;
                         edges_count++;

                     }
                     else
                         pos_value = 0;

                     if (test_type == QString("FULL"))
                         pos_value++;
                     if (pos_value != 0)
                         row_edge_n++;
                     values[key] = pos_value;

                }

            }

             outp_file << pos_value << " ";
        }
        outp_file << endl;

       }
   }

   qDebug()  << "\t\tEdges: " << edges_count;

   outp_file.close();
}



/*void run_tests(QXmlStreamWriter& xml, QString file_name) {
    BaseInterface* interface_class;
    double result;

    xml.writeStartElement(file_name);

    // Чтобы тест не расписывать, вот один прекрасный макрос.
#define one_test(x) try{\
    interface_class = new (x);\
    qDebug() << "\tTesting " << #x;\
    result = interface_class->run_performance_test(file_name.toStdString());\
    xml.writeTextElement(QString(#x), QString::number(result));\
    delete interface_class;\
    }\
    catch(...) {\
        qDebug() << "\tERROR! On testing " << QString(#x);\
    }

    one_test(PrimaBinTreeDGPP);
    one_test(PrimaSimpleDGPP);

    one_test(PrimaBinTreeVSSS);
    one_test(PrimaSimpleVSSS);

    one_test(PrimaBinTreeVKB);
    one_test(PrimaSimpleVKB);

    xml.writeEndElement();
}
*/

template<typename test_subj_type>
void run_performance_tests(string test_name, ifstream& outp, int test_v, int test_e) {

   for(auto& test_iter : test_names) {
         BaseInterface* interface_class = new test_subj_type;
         double result = interface_class->run_performance_test(test_name);
         outp << test_v << ";" << test_e << ";" << result << endl;

   }

}

/*
 *  Аргументы:
 *  0 - имя программы (стандартно)
 *  1 - надо ли выполнять генерацию тестов: 1 - надо, 0 - считаем, что сами тесты сгенерированы
 *  2... - по тройкам идёт следущая информация: количество узлов, количество рёбер, на нечётных - тип теста
 */
int main(int argc, char** argv)
{

    QFile file_results("results.xml");
    file_results.open(QIODevice::WriteOnly);

    QXmlStreamWriter xml(&file_results);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("DMM");

    bool gen_test = (QString(argv[1]) == QString("1") ? true : false);

    const int agr_per_test = 3;

    vector<string> test_files;

    for (int argi = 2; argi < argc; argi += agr_per_test) {
        int test_n = (argi-agr_per_test)/agr_per_test + 1;
        // Размер теста
        int test_size_v = QString(argv[argi]).toInt();
        int test_size_e = QString(argv[argi+1]).toInt();
        QString test_type = QString(argv[argi+2]);

        qDebug() << "Test " << test_n << ": " << test_size_v << " "<< test_size_e << " " << test_type;

        // Сформируем файл с тестовым графом
        QString test_file = QString("performance_") + QString::number(test_size_v) + QString("_") + QString::number(test_size_e) + "_" + test_type + QString(".txt");
        test_files.push_back(test_file.toStdString());
        if (gen_test) {
            qDebug() << "\tCreating test matrix " << test_file;
            create_performance_test(test_size_v, test_size_e, test_type, test_file);
        }
       // run_tests(xml, test_file);
        qDebug() << "Test generation ended";
        file_results.flush();
    }

    xml.writeEndDocument();

    file_results.close();
    return 0;
}
