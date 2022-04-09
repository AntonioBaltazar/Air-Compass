#include <sqlite3.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "database.h"
#include "graphreader.h"

using namespace std;
using namespace GraphReader;

void Database::setup_db()
{      
  char *queries_airplane = "INSERT INTO Airplane(Name,Type,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Airbus-A380','Long',15200,1575,310000,525);"\
                  "INSERT INTO Airplane(Name,Type,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Boeing-707','Long',11185,567,90200,189);"\
                  "INSERT INTO Airplane(Name,Type,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Airbus-A320','Medium',5800,360,24210,180);"\
                  "INSERT INTO Airplane(Name,Type,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Boeing-737','Medium',1353,297,18000,135);"\
                  "INSERT INTO Airplane(Name,Type,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Q-400','Short',2000,82,6500,80);"\
                  "INSERT INTO Airplane(Name,Type,Autonomy,Consumption,Tank_capacity,Seats) VALUES('ATR-72','Short',1600,144,6250,72);";

  char *queries_airport = "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_parking_to_runway,Delay_landing,Delay_anticolision,X,Y) VALUES('Paris-Charles-de-Gaulle','Paris',49.009691,2.547925,4,10,6,3,1,0,0,639,329);"\
                  "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_parking_to_runway,Delay_landing,Delay_anticolision,X,Y) VALUES( 'Aeroport international John F. Kennedy','New York',40.641766, -73.780968,4,11,6,4,4,0,0,315,376);"\
                  "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_parking_to_runway,Delay_landing,Delay_anticolision,X,Y) VALUES( 'Kingsford Smith International Airport','Sydney',-33.947346,151.179428,3,7,5,3,1,0,0,1248,736);"\
                  "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_parking_to_runway,Delay_landing,Delay_anticolision,X,Y) VALUES( 'International Airport of Shanghai-Pudong','Shanghai', 31.14340,121.80500,5,20,4,4,1,0,0,1129,422);"\
                  "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_parking_to_runway,Delay_landing,Delay_anticolision,X,Y) VALUES( 'International Airport OR Tambo de Johannesbourg','Johannesbourg',-26.134789,28.240528,2,6,3,4,1,0,0,744,676);"\
                  "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_parking_to_runway,Delay_landing,Delay_anticolision,X,Y) VALUES( 'International Airport of Sao Paulo/Guarulhos','Sao Paulo',-23.43455,-46.47813,4,317,2,6,3,4,1,438,681);";
  
  send_values(queries_airplane);
  send_values(queries_airport);
}


void Database::send_values(char* query){
  //Database's opening in order to establish a connexion
  if (sqlite3_open("Database.db", &m_database)) cout << "Error opening Database.db\n";

  //Sending a query to our database and checking for proper operation
  if (sqlite3_exec(m_database,query, NULL, NULL, NULL)) cout << "Error executing sql statement\n";
  
  //We close our database
  sqlite3_close(m_database);
}

void Database::send_values(){
  //Database's opening in order to establish a connexion
  if (sqlite3_open("Database.db", &m_database)) cout << "Error opening Database.db\n";

  //Sending a query to our database and checking for proper operation
  if (sqlite3_exec(m_database,get_sql_query(), NULL, NULL, NULL)) cout << "Error executing sql statement\n";
  
  //We close our database
  sqlite3_close(m_database);
}


void Database::create_fleet_txt_file(){
    vector<Airplane> bank;
    vector<Airplane> fleet;

    srand(time(nullptr));
    bank = read_plane_txt_file();

    /*
    for (int i = 0; i < nb_planes; i++) {
        fleet.push_back(bank[rand()%(6)]);
        fleet[i].set_id(i);
    }*/

    //set_airplane(bank);
    set_fleet(bank);

}

void Database::setup_txt(){
  set_airports(GraphReader::load_airports("graph.txt"));
  create_fleet_txt_file();
}


 void Database::display_airports() {          
    for(auto& el:get_airports()){
        el.display();
        std::cout << "\n ---- \n";
    }
}

void Database::display_fleet() {          
    for(auto& el:get_fleet()){
        el.display();
        std::cout << "\n ---- \n";
    }
}



