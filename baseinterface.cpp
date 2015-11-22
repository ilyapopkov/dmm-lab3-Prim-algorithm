#include "baseinterface.h"

/**
 * @brief BaseInterface::read_from_file
 * @param file_name - path and name to file with matrix format:
 *  size - number of vertex
 *  11 12 13 - Adjacency matrix
 *  21 22 23
 *  31 32 33
 * @param dense_matrix - read to dense matrix
 * @return true - if all ok, else return false
 */
bool BaseInterface::read_from_file(string file_name, bool dense_matrix)
{
    return read_from_file_service(file_name, false, dense_matrix);
}

/**
 * @brief BaseInterface::read_from_file
 * @param file_name - path and name to file with matrix format:
 *  size - number of vertex
 *  11 12 13 - Adjacency matrix of Minimum spanning tree
 *  21 22 23
 *  31 32 33
 * @param dense_matrix - write from dense matrix
 * @return true - if all ok, else return false
 */
bool BaseInterface::write_to_file(string file_name, bool dense_matrix)
{
    ofstream out_file(file_name.c_str());
    if(!out_file.good()) return false;

    if(dense_matrix) {
        out_file << DenseMatrix.size() << endl;
        for(size_t i = 0; i < DenseMatrix.size(); ++i) {
            for(size_t j = 0; j < DenseMatrix[i].size(); ++j)
                out_file << DenseMatrix[i][j] << " ";
            out_file << endl;
        }
    }
    else {
        convert_to_str();
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
    }

    return true;
}

bool BaseInterface::read_from_file_service(string file_name, bool is_unit_test, bool dense_matrix=false)
{
    ifstream in_file(file_name.c_str());
    if(!in_file.good()) return false;

    if(dense_matrix) {
        if(is_unit_test) {
            in_file >> size_answer;
            DenseMatrixAnswer.resize(size_answer);
            for(size_t i = 0; i < DenseMatrixAnswer.size(); ++i) {
                DenseMatrixAnswer[i].resize(size_answer);
                for(size_t j = 0; j < DenseMatrixAnswer[i].size(); ++j)
                    in_file >> DenseMatrixAnswer[i][j];
            }

        }
        else {
            in_file >> size;
            DenseMatrix.resize(size);
            for(size_t i = 0; i < DenseMatrix.size(); ++i) {
                DenseMatrix[i].resize(size);
                for(size_t j = 0; j < DenseMatrix[i].size(); ++j)
                    in_file >> DenseMatrix[i][j];
            }
        }
    }
    else {
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
        ig.resize(curr_size+1);
        gg.reserve(curr_size*curr_size);
        jg.reserve(curr_size*curr_size);
        if(is_unit_test)
            ig_answer.push_back(0);
        else
            ig[0] = 0;
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
                } else if(tmp == 0 && is_unit_test) {
                    for(int k = ig[i]; k < ig[i+1]; k++) {
                        if(jg[k] == j) {
                            gg_answer.push_back(tmp);
                            jg_answer.push_back(j);
                            count ++;
                            break;
                        }
                    }
                }
            }
            if(is_unit_test)
                ig_answer.push_back(count);
            else
                ig[i+1] = count;
        }
        in_file.close();

        if(!is_unit_test)
            convert_from_str();

        if(count == 0)
            return false;
    }
    return true;
}

void BaseInterface::convert_from_str()
{
    return;
}

void BaseInterface::convert_to_str()
{
    return;
}

size_t BaseInterface::run_tests()
{
    if(test1() == 0)
        cout << "1\t[OK]" << endl;
    else
        cout << "1\t[FAIL]" << endl;
    clear();
    if(test2() == 0)
        cout << "2\t[OK]" << endl;
    else
        cout << "2\t[FAIL]" << endl;
    clear();
    if(test3() == 0)
        cout << "3\t[OK]" << endl;
    else
        cout << "3\t[FAIL]" << endl;

    if(test4() == 0)
        cout << "4\t[OK]" << endl;
    else
        cout << "4\t[FAIL]" << endl;
    clear();
    return 0;
}

void BaseInterface::clear()
{
    gg.clear();
    ig.clear();
    jg.clear();
    size = 0;
    gg_answer.clear();
    ig_answer.clear();
    jg_answer.clear();
    size_answer = 0;
}

bool BaseInterface::read_answer_from_file(string file_name, bool dense_matrix=false)
{
    return read_from_file_service(file_name, true, dense_matrix);
}

size_t BaseInterface::compare()
{
    if(DenseMatrix.size() == 0) {
        if(size != size_answer) return 1;
        if(ig.size() != ig_answer.size()) return 2;
        if(gg.size() != gg_answer.size()) return 3;
        if(jg.size() != jg_answer.size()) return 4;
        for(size_t i = 0; i < ig.size(); i++)
            if(ig[i] != ig_answer[i]) return 5;
        for(size_t i = 0; i < gg.size(); i++)
            if(gg[i] != gg_answer[i]) return 6;
        for(size_t i = 0; i < jg.size(); i++)
            if(jg[i] != jg_answer[i]) return 7;
    }
    else {
        for(size_t i = 0; i < DenseMatrixAnswer.size(); ++i)
            for(size_t j = 0; j < DenseMatrixAnswer[i].size(); ++j)
                if(DenseMatrixAnswer[i][j] != DenseMatrix[i][j]) return 8;
    }

    return 0;
}

size_t BaseInterface::test1()
{
    bool dense = (DenseMatrix.size() > 0);
    read_from_file("UnitTests/test1.txt", dense);
    solve();
    read_answer_from_file("UnitTests/test1_answer.txt", dense);
    return compare();
}

size_t BaseInterface::test2()
{
    bool dense = (DenseMatrix.size() > 0);
    read_from_file("UnitTests/test2.txt", dense);
    solve();
    convert_to_str();
    read_answer_from_file("UnitTests/test2_answer.txt", dense);
    return compare();
}

size_t BaseInterface::test3()
{
    bool dense = (DenseMatrix.size() > 0);
    read_from_file("UnitTests/test3.txt", dense);
    solve();
    convert_to_str();
    read_answer_from_file("UnitTests/test3_answer.txt", dense);
    return compare();
}

size_t BaseInterface::test4()
{
    bool dense = (DenseMatrix.size() > 0);
    read_from_file("UnitTests/test4.txt", dense);
    solve();
    convert_to_str();
    read_answer_from_file("UnitTests/test4_answer.txt", dense);
    return compare();
}


double BaseInterface::run_performance_test(string file_name) {
    QString class_name = typeid(*this).name();
    qDebug() << "\t\t" << class_name << " reading";
    bool read_res =  read_from_file(file_name, false);
    if (!read_res) {
        qDebug() << "\t\tReading error!";
        throw;
    }
    qDebug()  << "\t\t" << class_name << " solving";

    LARGE_INTEGER start, stop, timetime, fr;
    double time;
    QueryPerformanceFrequency(&fr);
    QueryPerformanceCounter(&start);

    solve();

    QueryPerformanceCounter(&stop);
    timetime.QuadPart = stop.QuadPart - start.QuadPart;
    time = (double)timetime.QuadPart / (double)fr.QuadPart;

    qDebug()  << "\t\t" << class_name << " writing";
    write_to_file(file_name + class_name.toStdString());

    return time;
}
