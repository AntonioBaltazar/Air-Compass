#include <iostream>
#include <fstream>
#include <string>
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

void Airplane::choose_plane(){

    int test=0;
    string name;
    cout << endl;
    cout << " Write the name of the plane" << endl;
    cin >> name;
    

    while (test==0)
    {
        if( name == "Airbus-A380") test++;
        
        if( name == "Boeing-707") test++;

        if( name == "Airbus-A320") test++;
        
        if( name == "Boeing-737") test++;
        
        if( name == "ATR-72") test++;
        
        if( name == "Q-400") test++;

        if (test == 0 ){
            cout <<"Write a real name of the place " << endl;
            cin >> name;
        }
    }    
}

void Airplane::plane(){

    cout << "Airbus-A380" << endl;
    cout << "Boeing-707" << endl;
    cout << "Airbus-A320" << endl;
    cout << "Boeing-737" << endl;
    cout << "ATR-72" << endl;
    cout << "Q-400" << endl;
}
void Airplane::aeroport(){
    system("clear");
    cout << "Paris"<< endl;
    cout << "Sydney"<< endl;
    cout << "New_York"<<endl;
    cout << "Shanghai"<<endl;
    cout << "Johannesbourg"<<endl;
    cout << "Sao-Paulo"<<endl;
}

void Airplane::choose_airport(){
    
    int test=0;
    string aeroport;
    cout << "Enter the name of the destination"<< endl;
    cin >> aeroport;
    while(test==0)
    {
        if (aeroport == "Paris") test++;
    
        if (aeroport == "Sydney") test++;

        if (aeroport == "New_York") test++;

        if (aeroport == "Shanghai") test++;

        if (aeroport == "Johannesbourg") test++;

        if (aeroport == "Sao-Paulo") test++;

        if(test == 0)
        {
            cout << "Enter a right name of an destination" << endl;
            cin >> aeroport;
        }
    }
}