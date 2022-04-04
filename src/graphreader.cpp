#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdarg>
#include "graphreader.h"
#include "airplane.h"
#include <fstream>

using namespace GraphReader;
using namespace std;

void GraphReader::test() {
    std::cout << "debugging";
}

void GraphReader::load_graph(std::string _file_name, Graph& _graph) {
    ifstream ifs{_file_name};
    if (!ifs) throw runtime_error("Can't open " + _file_name);

    int oriented(0), order(0), size(0);
    // fget_int(ifs, oriented, "Unable to know if graph is oriented");
    // fget_int(ifs, order, "Can't read order of graph");
    // fget_int(ifs, size, "Can't read size of graph");
    fget_int(ifs, "Error", {&oriented, &order, &size});
    std::cout << "debugging : " << oriented << " " << order << " " << size;

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

vector<Airplane> read_plane() {
    ifstream file("planes.txt");
    vector<Airplane> planes;
    Airplane temp;
    string content="a";
    int type, capacity,consumption,autonomy, nb_seats ;

    if (!file)
        throw runtime_error("Fail to open file 'planes.txt' in reading only mode");
    
    while(!file.eof()){
        file >> content; 
        if(content == "") break;
        temp.set_name(content);
 
        fget_int(file,"Reading plane's data",{&type, &capacity, &consumption, &autonomy, &nb_seats}); // type : long short or medium
        
        temp.set_type(type == 1 ? AirplaneType::Long : ( type == 2 ? AirplaneType::Medium : AirplaneType::Short));
        temp.set_fuel_capacity(capacity);
        temp.set_consumption(consumption);
        temp.set_autonomy(autonomy);   
        temp.set_nb_seats(nb_seats);

        planes.push_back(temp);
    }

    return planes;
}
