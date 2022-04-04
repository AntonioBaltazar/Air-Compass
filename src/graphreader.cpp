#include <iostream>
#include <fstream>
#include <cstdarg>
#include "graphreader.h"

using namespace GraphReader;
using namespace std;

void GraphReader::test() {
    cout << "debugging";
}

void GraphReader::load_graph(std::string _file_name, Graph& _graph) {
    ifstream ifs{_file_name};
    if (!ifs) throw runtime_error("Can't open " + _file_name);

    int oriented(0), order(0), size(0);
    // fget_int(ifs, oriented, "Unable to know if graph is oriented");
    // fget_int(ifs, order, "Can't read order of graph");
    // fget_int(ifs, size, "Can't read size of graph");
    fget_int(ifs, "Error", {&oriented, &order, &size});
    cout << "debugging : " << oriented << " " << order << " " << size;

    _graph.set_oriented(oriented);
    _graph.set_nb_vertices(order);
    
    for (int i = 0; i < size; i++) {
        
    }
    
    

}

void GraphReader::fget_int(ifstream& _ifs, std::string _error, vector<int*> _args) {
    for (auto& _arg : _args) {
        _ifs >> *_arg;
        if (_ifs.fail()) throw runtime_error(_error);
    }
}