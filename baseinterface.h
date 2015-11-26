#ifndef BASEINTERFACE_H
#define BASEINTERFACE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <typeinfo>
#include <QDebug>

using namespace std;

/*
 * ���������, ���� � ����-������������:
 * ����������� �.�.
 * ������� �.�.
 * ������ �.�.
 * ��������� �.�.
*/


class BaseInterface
{
protected:
    size_t size;
    vector<int> gg;
    vector<size_t> ig;
    vector<size_t> jg;
    vector<vector<int> > DenseMatrix; //матрица в плотном формате, необходима только для одного из вариантов, по-умолчанию ничего не хранит

    virtual void convert_from_str(); // Необходимо переопределить в классе-потомке, если необходимо перевести данные в свой формат
    virtual void convert_to_str(); // Необходимо переопределить в классе-потомке, если необходимо перевести данные из своего формата в строчный

    //For Unit-test
    size_t size_answer;
    vector<int> gg_answer;
    vector<size_t> ig_answer;
    vector<size_t> jg_answer;
    vector<vector<int> > DenseMatrixAnswer;

    bool read_from_file_service(string file_name, bool is_unit_test, bool dense_matrix);
    bool read_answer_from_file(string file_name, bool dense_matrix);
    size_t compare();
    void clear();
    size_t test1();
    size_t test2();
    size_t test3();
    size_t test4();
public:

    bool read_from_file(string file_nam, bool dense_matrix=false);
    bool read_from_file_CR(string file_name, bool dense_matrix=false);      // ������ � �������� �������
    bool write_to_file(string file_name, bool dense_matrix=false);
    virtual void solve() = 0;

    //For Unit-test
    size_t run_tests();
    double run_performance_test(string file_name);
};

#endif // BASEINTERFACE_H
