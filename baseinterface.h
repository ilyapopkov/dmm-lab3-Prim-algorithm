#ifndef BASEINTERFACE_H
#define BASEINTERFACE_H

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
public:

    bool read_from_file(string file_name);
    bool write_to_file(string file_name);
    virtual void solve() = 0;
};

#endif // BASEINTERFACE_H
