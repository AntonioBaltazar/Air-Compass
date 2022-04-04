#include <iostream>
#include <fstream>
#include "airplane.h"

using namespace std;

void Airplane::display(){

    cout << "\nName : " << get_name() << endl;
    cout << "Tank capacity : " << get_fuel_capacity() << endl;
    cout << "Consumption : " << get_consumption() << endl;
    cout << "Autonomy : " << get_autonomy() << endl;
    cout << "Nb seats : " << get_nb_seats() << endl;
    
}