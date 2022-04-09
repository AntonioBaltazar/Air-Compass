#ifndef GRAPHREADER_H_INCLUDED
#define GRAPHREADER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstdarg>
#include <vector>
#include "graph.h"
#include "airplane.h"

namespace GraphReader {
    void test();
    void fget_int(std::ifstream& _ifs, std::string _error, std::vector<int*> _args);
    void load_graph(std::string _file_name, Graph& _graph);
    std::vector<Airport> load_airports(std::string _file_name);
    std::vector<std::string> deserialize(std::string _str);
    std::vector<Airplane> read_plane_txt_file();
};

std::vector<Airplane> read_plane_file();

#endif // GRAPHREADER_H_INCLUDED