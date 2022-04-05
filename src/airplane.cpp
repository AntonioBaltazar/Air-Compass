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

void Airplane::choose(){

    int test=0;
    string name;
    cout << endl;
    cout << " Write the name of the plane" << endl;
    cin >> name;
    do{
        if( name == "Airbus-A380")
            test++;
        
        if( name == "Boeing-707")
            test++;

        if( name == "Airbus-A320")
            test++;
        
        if( name == "Boeing-737")
            test++;
        
        if( name == "ATR-72")
            test++;
        
        if( name == "Q-400")
            test++;

        if (test == 0 )
            cout <<"Write a real name of the place " << endl;
            cin >> name;
    }
    while( test == 1 );


    
}