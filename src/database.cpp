#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <vector>
#include "database.h"

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){

    for(int i = 0; i < argc; i++) {        
       // Show column name, value, and newline
        cout << azColName[i] << ": " << argv[i] << endl;
    }

    // Insert a newline
    cout << endl;

    // Return successful
    return 0;
}


void Database::setup_db()
{
    sqlite3 *db;
    string db_path = "Database.db";
    char *queries_airplane = "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Airbus-A380',15200,1575,310000,525);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Boeing-707',11185,567,90200,189);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Airbus-A320',5800,360,24210,180);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Boeing-737',1353,297,18000,135);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Q-400',2000,82,6500,80);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('ATR-72',1600,144,6250,72);";

    char *queries_airport = "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_landing,Delay_anticolision) VALUES('Paris-Charles-de-Gaulle','Paris',49.009691,2.547925,4,10,6,3,1,0,0 );"\
                    "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_landing,Delay_anticolision) VALUES( 'Aeroport international John F. Kennedy','New York',40.641766, -73.780968,4,11,6,4,4,0,0 );"\
                    "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_landing,Delay_anticolision) VALUES( 'Kingsford Smith International Airport','Sydney','-33.947346,151.179428,3,7,5,3,1,0,0 );"\
                    "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_landing,Delay_anticolision) VALUES( 'International Airport of Shanghai-Pudong','Shanghai', 31.14340,121.80500,5,20,4,4,1,0,0 );"\
                    "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_landing,Delay_anticolision) VALUES( 'Aeroport international OR Tambo de Johannesbourg','Johannesbourg',-26.134789,28.240528,2,6,3,4,1,0,0);"\
                    "INSERT INTO Airport(Name,Location,Lattitude,Longitude,Number_runaway,Number_parking,Delay_between_flights,Standby_flight_time,Delay_landing,Delay_anticolision) VALUES( 'Aeroport international de Sao Paulo/Guarulhos','Sao Paulo',-23.43455,-46.47813,4,317,2,6,3,4,1);";
    char *err_msg= 0;
    int rc = 0;

     
    if(!sqlite3_open(db_path.c_str(), &db))
    {
        rc = sqlite3_exec(db, queries_airplane, callback, 0, &err_msg);

            if( rc != SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
        } else 
            cout << "Table Airplane created successfully\n";

        rc = sqlite3_exec(db, queries_airport, callback, 0, &err_msg);

            if( rc != SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
        } else 
            cout << "Table Airport created successfully\n";
        
    }else cout << "Failed to open 'Database.db'\n";
    sqlite3_close(db);
}