#include <iostream>
#include "graphreader.h"
#include "airplane.h"
#include <fstream>

using namespace GraphReader;
using namespace std;

void GraphReader::test(){
    cout << "debugging";
}

void GraphReader::load_graph(std::string _file_name, Graph &_graph){
    cout << "test";
}

vector<string> strSplit(string str, string delimiter)
{
    std::vector<std::string> res;
    size_t position = 0;

    while ((position = str.find(delimiter)) != string::npos)
    {
        res.push_back(str.substr(0, position));
        str.erase(0, position + delimiter.length());
    }
    res.push_back(str);
    return res;
}

vector<Airplane> read_plane() {
    ifstream file("planes.txt");
    vector<Airplane> planes;
    Airplane temp;
    string content, bin;

    if (!file)
        throw runtime_error("Fail to open file 'planes.txt' in reading only mode");

    for (int i = 0; i < 8; i++) // Comments reading
     {
        file >> content;
        //cout << "\nComments : " << content;
     }    

    for (int i = 0; i < 6; i++){                    // Planes information reading
        file >> content; // name
         cout << "\nName : " << content;
        if (file.fail())
            throw runtime_error("Couldn't read plane's name");
        temp.set_name(content);

        file >> content; // type : long short or medium
        if (file.fail())
            throw runtime_error("Couldn't read plane's type");
        if (i < 2)
            temp.set_type(AirplaneType::Long);
        else if (i >= 2 && i < 4)
            temp.set_type(AirplaneType::Medium);
        else if (i >= 4 && i < 6)
            temp.set_type(AirplaneType::Medium);

        file >> content; // Fuel tank capacity in L
        if (file.fail())
            throw runtime_error("Couldn't read plane's fuel tank capacity");
        temp.set_fuel_capacity(atoi(content.c_str()));

        file >> content; // Consumption in L/100km
        if (file.fail())
            throw runtime_error("Couldn't read plane's consumption");
        temp.set_consumption(atoi(content.c_str()));

        file >> content; // Autonomy in km
        if (file.fail())
            throw runtime_error("Couldn't read plane's autonomy");
        temp.set_autonomy(atoi(content.c_str()));

        file >> content; // Number of seats
        if (file.fail())
            throw runtime_error("Couldn't read plane's number of seats");
        temp.set_nb_seats(atoi(content.c_str()));

        planes.push_back(temp);
    }
    cout << "Reading's over";
    return planes;
}
