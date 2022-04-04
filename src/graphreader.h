#ifndef GRAPHREADER_H_INCLUDED
#define GRAPHREADER_H_INCLUDED

#include <fstream>
#include <cstdarg>
#include <vector>
#include "graph.h"

namespace GraphReader {
    void test();
    void fget_int(std::ifstream& _ifs, std::string _error, std::vector<int*> _args);
    void load_graph(std::string _file_name, Graph& _graph);
};

#endif // GRAPHREADER_H_INCLUDED