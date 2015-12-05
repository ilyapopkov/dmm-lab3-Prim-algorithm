#include <iostream>

#include <fstream>
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

            int min_i = max(i, j);
            int max_i = min(i, j);
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


struct test_info {
    string test_name;
    int test_v;
    int test_e;

    test_info(QString s, int v, int e) {
        test_name = s.toStdString();
        test_v = v;
        test_e = e;
    }

};


template<typename test_subj_type>
void run_performance_tests(vector<test_info>& tests, ofstream& outp) {

    outp << typeid(test_subj_type).name() << ";" <<  endl;
    qDebug() << "Testing " << typeid(test_subj_type).name();

   for(auto& test : tests) {
        qDebug() << "\t"  << test.test_name.c_str();
         BaseInterface* interface_class = new test_subj_type;
         double result = interface_class->run_performance_test(test.test_name);
         outp << test.test_v << ";" << test.test_e << ";" << result << endl;

         delete interface_class;

   }

   outp << endl;
   outp.flush();

}

/*
 *  Аргументы:
 *  0 - имя программы (стандартно)
 *  1 - надо ли выполнять генерацию тестов: 1 - надо, 0 - считаем, что сами тесты сгенерированы
 *  2 - имя файла, где хранится информация о тестах
 */
int main(int argc, char** argv)
{
    if (argc != 3)
        throw;

    bool gen_test = (QString(argv[1]) == QString("1") ? true : false);

    ifstream test_file(argv[2]);

    vector<test_info> tests;
    int test_n = 0;

    while (!test_file.eof()) {
        test_n++;
        // Размер теста
        int test_size_v;
        int test_size_e;
        string test_type_std;

        test_file >> test_size_v >> test_size_e >> test_type_std;

        QString test_type = QString(test_type_std.c_str());
        qDebug() << "Test " << test_n << ": " << test_size_v << " "<< test_size_e << " " << test_type;

        // Сформируем файл с тестовым графом
        QString test_file = QString("performance_") + QString::number(test_size_v) + QString("_") + QString::number(test_size_e) + "_" + test_type + QString(".txt");

        tests.push_back(test_info(test_file, test_size_v, test_size_e));

        if (gen_test) {
            qDebug() << "\tCreating test matrix " << test_file;
            create_performance_test(test_size_v, test_size_e, test_type, test_file);
        }
        qDebug() << "Test generation ended";
    }

    ofstream outp("results.cvs");

    run_performance_tests<PrimaSimpleDGPP>(tests, outp);
    run_performance_tests<PrimaSimpleVKB>(tests, outp);
    run_performance_tests<PrimaSimpleVSSS>(tests, outp);


    run_performance_tests<PrimaBinTreeDGPP>(tests, outp);
    run_performance_tests<PrimaBinTreeVKB>(tests, outp);
    run_performance_tests<PrimaBinTreeVSSS>(tests, outp);

    outp.close();

    qDebug() << "Tests ended";

    return 0;
}
