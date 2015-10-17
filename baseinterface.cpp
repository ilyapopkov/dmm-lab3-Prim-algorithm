#include "baseinterface.h"

/**
 * @brief BaseInterface::read_from_file
 * @param file_name - path and name to file with matrix format:
 *  size - number of vertex
 *  11 12 13 - Adjacency matrix
 *  21 22 23
 *  31 32 33
 * @return true - if all ok, else return false
 */
bool BaseInterface::read_from_file(string file_name)
{
    return read_from_file_service(file_name, false);
}

/**
 * @brief BaseInterface::read_from_file
 * @param file_name - path and name to file with matrix format:
 *  size - number of vertex
 *  11 12 13 - Adjacency matrix of Minimum spanning tree
 *  21 22 23
 *  31 32 33
 * @return true - if all ok, else return false
 */
bool BaseInterface::write_to_file(string file_name)
{
    ofstream out_file(file_name.c_str());
    if(!out_file.good()) return false;

    out_file << size << endl;
    for(size_t i = 0; i < size; i++) {
        for(size_t j = 0; j < size; j++) {
            bool flag = false;
            size_t k;
            for(k = ig[i]; k < ig[i+1] && !flag; k++)
                if(j == jg[k]) flag = true;
            if(flag)
                out_file << gg[k-1] << " ";
            else
                out_file << "0 ";
        }
        out_file << endl;
    }
    out_file.close();
    return true;
}

bool BaseInterface::read_from_file_service(string file_name, bool is_unit_test)
{
    ifstream in_file(file_name.c_str());
    if(!in_file.good()) return false;

    size_t curr_size;
    if(is_unit_test) {
        in_file >> size_answer;
        curr_size = size_answer;
    }
    else {
        in_file >> size;
        curr_size = size;
    }
    int tmp;
    if(is_unit_test)
        ig_answer.push_back(0);
    else
        ig.push_back(0);
    int count = 0;
    for(size_t i = 0; i < curr_size; i++) {
        for(size_t j = 0; j < curr_size; j++) {
            in_file >> tmp;
            if(tmp != 0) {
                if(is_unit_test) {
                    gg_answer.push_back(tmp);
                    jg_answer.push_back(j);
                }
                else {
                    gg.push_back(tmp);
                    jg.push_back(j);
                }
                count ++;
            }
        }
        if(is_unit_test)
            ig_answer.push_back(count);
        else
            ig.push_back(count);
    }
    in_file.close();
    if(count == 0)
        return false;
    return true;
}

size_t BaseInterface::run_tests()
{
    if(!test1() > 0)
        cout << "1\t[OK]" << endl;
    else
        cout << "1\t[FAIL]" << endl;

    if(!test2() > 0)
        cout << "2\t[OK]" << endl;
    else
        cout << "2\t[FAIL]" << endl;

    if(test3() > 0)
        cout << "3\t[OK]" << endl;
    else
        cout << "3\t[FAIL]" << endl;
    return 0;
}

bool BaseInterface::read_answer_from_file(string file_name)
{
    return read_from_file_service(file_name, true);
}

size_t BaseInterface::compare()
{
    if(size != size_answer) return 1;
    if(ig.size() != ig_answer.size()) return 2;
    if(gg.size() != gg_answer.size()) return 3;
    if(jg.size() != jg_answer.size()) return 4;
    for(size_t i = 0; i < ig.size(); i++)
        if(ig[i] != ig_answer[i]) return 5;
    for(size_t i = 0; i < gg.size(); i++)
        if(gg[i] != gg_answer[i]) return 6;
    for(size_t i = 0; i < ig.size(); i++)
        if(jg[i] != jg_answer[i]) return 7;

    return 0;
}

size_t BaseInterface::test1()
{
    read_from_file("UnitTests/test1.txt");
    solve();
    read_answer_from_file("UnitTests/test1_answer.txt");
    return compare();
}

size_t BaseInterface::test2()
{
    read_from_file("UnitTests/test2.txt");
    solve();
    read_answer_from_file("UnitTests/test2_answer.txt");
    return compare();
}

size_t BaseInterface::test3()
{
    read_from_file("UnitTests/test3.txt");
    solve();
    read_answer_from_file("UnitTests/test3_answer.txt");
    return compare();
}
