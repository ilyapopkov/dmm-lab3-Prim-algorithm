#ifndef BASEINTERFACE_H
#define BASEINTERFACE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class BaseInterface
{
protected:
    size_t size;
    vector<int> gg;
    vector<size_t> ig;
    vector<size_t> jg;

    void convert_from_str(); // Необходимо переопределить в классе-потомке, если необходимо перевести данные в свой формат
    void convert_to_str(); // Необходимо переопределить в классе-потомке, если необходимо перевести данные из своего формата в строчный

    //For Unit-test
    size_t size_answer;
    vector<int> gg_answer;
    vector<size_t> ig_answer;
    vector<size_t> jg_answer;

    bool read_from_file_service(string file_name, bool is_unit_test);
    bool read_answer_from_file(string file_name);
    size_t compare();
    void clear();
    size_t test1();
    size_t test2();
    size_t test3();
public:

    bool read_from_file(string file_name);
    bool write_to_file(string file_name);
    virtual void solve() = 0;

    //For Unit-test
    size_t run_tests();
};

#endif // BASEINTERFACE_H
