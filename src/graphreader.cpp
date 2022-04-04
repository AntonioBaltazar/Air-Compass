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
        if (_ifs.fail()) 
            throw runtime_error(_error);

    }
}

vector<Airplane> read_plane() {
    ifstream file("planes.txt");
    vector<Airplane> planes;
    Airplane temp;
    string content;
    int type, capacity,consumption,autonomy, nb_seats ;

    if (!file)
        throw runtime_error("Fail to open file 'planes.txt' in reading only mode");
    //while(getline(file,content)){
       getline(file,content);
        temp.set_name(content);

        fget_int(file,"Reading plane's data",{&type, &capacity, &consumption, &autonomy, &nb_seats}); // type : long short or medium
        
        if (type < 2)
            temp.set_type(AirplaneType::Long);
        else if (type >= 2 && type < 4)
            temp.set_type(AirplaneType::Medium);
        else if (type >= 4 && type < 6)
            temp.set_type(AirplaneType::Medium);

    //}
    // while(getline(file,content))
    //     if(content != "")
    //     {
    //         // if(content[0]==$)
    //             // temp.push_back(strSpl)
    //     }

    // for (int i = 0; i < 8; i++) // Comments reading
    //  {
    //     file >> content;
      
    // for (int i = 0; i < 6; i++){                    // Planes information reading
    //     file >> content; // name
    //      cout << "\nName : " << content;
    //     if (file.fail())
    //         throw runtime_error("Couldn't read plane's name");
    //     temp.set_name(content);

    //     file >> content; // type : long short or medium
    //     if (file.fail())
    //         throw runtime_error("Couldn't read plane's type");
    //     if (i < 2)
    //         temp.set_type(AirplaneType::Long);
    //     else if (i >= 2 && i < 4)
    //         temp.set_type(AirplaneType::Medium);
    //     else if (i >= 4 && i < 6)
    //         temp.set_type(AirplaneType::Medium);

    //     file >> content; // Fuel tank capacity in L
    //     if (file.fail())
    //         throw runtime_error("Couldn't read plane's fuel tank capacity");
    //     temp.set_fuel_capacity(atoi(content.c_str()));

    //     file >> content; // Consumption in L/100km
    //     if (file.fail())
    //         throw runtime_error("Couldn't read plane's consumption");
    //     temp.set_consumption(atoi(content.c_str()));

    //     file >> content; // Autonomy in km
    //     if (file.fail())
    //         throw runtime_error("Couldn't read plane's autonomy");
    //     temp.set_autonomy(atoi(content.c_str()));

    //     file >> content; // Number of seats
    //     if (file.fail())
    //         throw runtime_error("Couldn't read plane's number of seats");
    //     temp.set_nb_seats(atoi(content.c_str()));

    //     planes.push_back(temp);
    // }
    cout << "Reading's over";
    return planes;
}
