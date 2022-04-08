#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <sqlite3.h>
#include "aerialnetwork.h"
#include "graphreader.h"
#include <stdio.h>

using namespace std;

void AerialNetwork::create_fleet()
{
    vector<Airplane> bank;
    vector<Airplane> fleet;
    int nb_planes = 10;
    srand(time(nullptr));
    bank = read_plane_file();
    /*
    for (int i = 0; i < nb_planes; i++) {
        fleet.push_back(bank[rand()%(6)]);
        fleet[i].set_id(i);
    }*/

    //set_airplane(bank);
    set_fleet(bank);

}

// void AerialNetwork::create_fleet_db()
// {
//     // Pointer to SQLite connection
//     sqlite3 *db;

//     // Save any error messages
//     char *zErrMsg = 0;

//     // Save the result of opening the file
//     int rc;

//     // Save any SQL
//     string sql;

//     // Save the result of opening the file
//     rc = sqlite3_open("example.db", &db);
    
//     if( rc ){
//         // Show an error message
//         cout << "DB Error: " << sqlite3_errmsg(db) << endl;
//         // Close the connection
//         sqlite3_close(db);
//         // Return an error
//     }

//     // Save SQL to create a table
//     sql = "CREATE TABLE PEOPLE ("  \
//       "ID INT PRIMARY KEY     NOT NULL," \
//       "NAME           TEXT    NOT NULL);";
    
//     // Run the SQL (convert the string to a C-String with c_str() )
//     rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

//     // Save SQL insert data
//     sql = "INSERT INTO PEOPLE ('ID', 'NAME') VALUES ('3','Jeff');";
    
//     // Run the SQL (convert the string to a C-String with c_str() )
//     rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

//     // Save SQL insert data
//     sql = "INSERT INTO PEOPLE ('ID', 'NAME') VALUES ('2','Dan');";
    
//     // Run the SQL (convert the string to a C-String with c_str() )
//     rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

//     // Save SQL insert data
//     sql = "INSERT INTO PEOPLE ('ID', 'NAME') VALUES ('1','Cara');";
    
//     // Run the SQL (convert the string to a C-String with c_str() )
//     rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

//     // Save SQL insert data
//     sql = "SELECT * FROM 'PEOPLE';";
    
//     // Run the SQL (convert the string to a C-String with c_str() )
//     rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    
//     // Close the SQL connection
//     sqlite3_close(db);

// }

// static int callback(void *NotUsed, int argc, char **argv, char **azColName){

//     // int argc: holds the number of results
//     // (array) azColName: holds each column returned
//     // (array) argv: holds each value

//     for(int i = 0; i < argc; i++) {
        
//         // Show column name, value, and newline
//         cout << azColName[i] << ": " << argv[i] << endl;
    
//     }

//     // Insert a newline
//     cout << endl;

//     // Return successful
//     return 0;
// }

// void request_data()
// {
//     // rc not handled in this abbreviated code

//   sqlite3 *db;
//   sqlite3_stmt *stmt;
//   char * sql;

//   const char * tail;
//   int rc;

//   char * dbName = "Database.db";
//   int myIndex = 0;

//   char * myLocation1;
//   string myLocation2;   

//   rc = sqlite3_open(dbName, &db);

//   sql = "SELECT NAME FROM Airplane ";
//   rc = sqlite3_prepare(db, sql, sizeof(sql), &stmt, &tail);
//   sqlite3_bind_int(stmt, 1, myIndex);
//   rc = sqlite3_step(stmt);

//   myLocation1 = (char*)sqlite3_column_text(stmt, 0);
//   myLocation2 = (char*)sqlite3_column_text(stmt, 0);
//     cout << "ok";
//   cout << "Name 1 : " << myLocation1;
//   cout << "Name 2 : " << myLocation2;

//   // can process myLocation1 & myLocation2 fine here

//   sqlite3_finalize(stmt); // data myLocation1 points to get corrupted
//   sqlite3_close(db);      // data myLocation2 points to gets further corrupted
// }
