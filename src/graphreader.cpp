#include <iostream>
#include <fstream>
#include "graphreader.h"

using namespace GraphReader;
using namespace std;

void GraphReader::test() {
    cout << "debugging";
}

void GraphReader::load_graph(std::string _file_name, Graph& _graph) {
    ifstream ifs{_file_name};
    if (!ifs) throw runtime_error("Can't open " + _file_name);

    int oriented, order, size;
    fget_int(ifs, oriented, "Unable to know if graph is oriented");
    fget_int(ifs, order, "Can't read order of graph");
    fget_int(ifs, size, "Can't read size of graph");

    _graph.set_oriented(oriented);
    _graph.set_nb_vertices(order);
    
    for (int i = 0; i < size; i++) {

    }


}

void GraphReader::fget_int(ifstream& _ifs, int& _var, std::string _error) {
    _ifs >> _var;
    if (_ifs.fail()) throw runtime_error(_error);
}