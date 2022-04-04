#include <iostream>
#include <fstream>
#include "airplane.h"

using namespace std;

void Airplane::display(){

    cout << "\nName : " << get_name() << endl;
    cout << "Type : ";
    if(get_type() == AirplaneType::Long) cout << "Long \n";
    else if (get_type() == AirplaneType::Medium)  cout << "Medium \n";
    else if (get_type() == AirplaneType::Short)  cout << "Short \n";
    cout << "Tank capacity : " << get_fuel_capacity() << endl;
    cout << "Consumption : " << get_consumption() << endl;
    cout << "Autonomy : " << get_autonomy() << endl;
    cout << "Nb seats : " << get_nb_seats() << endl;
    
}