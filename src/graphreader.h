#ifndef GRAPHREADER_H_INCLUDED
#define GRAPHREADER_H_INCLUDED

#include <fstream>
#include "graph.h"

namespace GraphReader {
    void test();
    void fget_int(std::ifstream& _ifs, int& _var, std::string _error);
    void load_graph(std::string _file_name, Graph& _graph);
};

#endif // GRAPHREADER_H_INCLUDED