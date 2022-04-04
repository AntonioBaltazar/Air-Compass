#ifndef GRAPHREADER_H_INCLUDED
#define GRAPHREADER_H_INCLUDED

#include <iostream>
#include "graph.h"
#include "airplane.h"

namespace GraphReader {
    void test();
    void load_graph(std::string _file_name, Graph& _graph);
};

std::vector<Airplane> read_plane();

#endif // GRAPHREADER_H_INCLUDED