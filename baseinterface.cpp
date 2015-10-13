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
    ifstream in_file(file_name.c_str());
    if(!in_file.good()) return false;

    in_file >> size;
    int tmp;
    ig.push_back(0);
    int count = 0;
    for(size_t i = 0; i < size; i++) {
        for(size_t j = 0; j < size; j++) {
            in_file >> tmp;
            if(tmp != 0) {
                gg.push_back(tmp);
                jg.push_back(j);
                count ++;
            }
        }
        ig.push_back(count);
    }
    in_file.close();
    if(count == 0)
        return false;
    return true;
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


