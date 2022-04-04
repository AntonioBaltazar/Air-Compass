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
    fget_int(ifs, "Unable to read graph's settings", {&oriented, &order, &size});
    _graph.set_oriented(oriented);
    _graph.set_nb_vertices(order);

    // Init vertices
    for (int i = 0; i < _graph.get_nb_vertices(); i++)
        _graph.get_vertices().push_back(Vertice());

    // Reading all edges
    int src(0), dist(0), weight(0);
    for (int i = 0; i < size; i++) {
        fget_int(ifs, "Can't read this ", {&src, &dist, &weight});
        _graph.get_vertices()[src].get_adjacent().push_back(make_pair(&(_graph.get_vertices()[dist]), weight));
            if (!_graph.is_oriented()) _graph.get_vertices()[dist].get_adjacent().push_back(make_pair(&(_graph.get_vertices()[src]), weight));
    }

    // Reading all airports
    string _str;
    getline(ifs, _str);
    for (int i = 0; i < _graph.get_nb_vertices(); i++) {
        getline(ifs, _str);
        vector<string> _strs = deserialize(_str);
        _graph.get_vertices()[i].get_airport() = Airport(_strs[0], _strs[1], {stod(_strs[2]), stod(_strs[3])}, stoi(_strs[4]), stoi(_strs[5]),
        stoi(_strs[6]), stoi(_strs[7]), stoi(_strs[8]), stoi(_strs[9]), stoi(_strs[10]));
    }
}

vector<string> GraphReader::deserialize(string _str) {
    for (const auto& _delimiter : vector<char>{'{', '}', '"'})
        _str.erase(std::remove(_str.begin(), _str.end(), _delimiter), _str.end());

    vector<string> res;
    size_t pos(0);
    // String spliter 
    string _delimiter = ",";
    while((pos = _str.find(_delimiter)) != string::npos) {
        res.push_back(_str.substr(0, pos));
        _str.erase(0, pos + _delimiter.size());
    }
    res.push_back(_str);
    return res;
}

void GraphReader::fget_int(ifstream& _ifs, std::string _error, vector<int*> _args) {
    for (auto& _arg : _args) {
        _ifs >> *_arg;
        if (_ifs.fail()) throw runtime_error(_error);
    }
}

vector<Airplane> read_plane_file() {
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
