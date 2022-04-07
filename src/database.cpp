#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <vector>

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

bool open_db(sqlite3 *db,string db_path)
{
   /* Open database */
   return !sqlite3_open(db_path.c_str(), &db);
}


void close_db(sqlite3 *db)
{
    sqlite3_close(db);
}

vector<string> airplane_creation_queries()
{
    vector<string> queries;

    queries.push_back("INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Airbus-A380',15200,1575,310000,525);");
    queries.push_back("INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Boeing-707',11185,567,90200,189);");
    queries.push_back("INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Airbus-A320',5700,360,24210,180);");
    queries.push_back("INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Boeing-737',1353,297,18000,135);");
    queries.push_back("INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('ATR-72',1600,144,6250,72);");

    return queries;
}

void setup_db()
{
    sqlite3 *db;
    string db_path = "Database.db";
    char *queries = "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Airbus-A380',15200,1575,310000,525);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Boeing-707',11185,567,90200,189);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Airbus-A320',5700,360,24210,180);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Boeing-737',1353,297,18000,135);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('ATR-72',1600,144,6250,72);";
    char *err_msg= 0;
    int rc = 0;

     
    if(sqlite3_open("Database.db", &db))
    {
            rc = sqlite3_exec(db, queries, callback, 0, &err_msg);
   
             if( rc != SQLITE_OK ){
                fprintf(stderr, "SQL error: %s\n", err_msg);
                sqlite3_free(err_msg);
            } else {
                fprintf(stdout, "Table created successfully\n");
            }
    }else cout << "NOP\n";
    close_db(db);
}

void  handle_db_plane()
{
    sqlite3 *db;
    string db_path = "Database.db";

    if(open_db(db,db_path))
        cout << "OK ! \n";
    else
        cout << "courage...\n";
    
}

void  create_db_plane()
{
   sqlite3 *db;
   char *err_msg= 0;
   int rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("Database.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql =  "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Airbus-A380',15200,1575,310000,525);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Boeing-707',11185,567,90200,189);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Airbus-A320',5700,360,24210,180);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('Boeing-737',1353,297,18000,135);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('ATR-72',1600,144,6250,72);"\
                    "INSERT INTO Airplane(Name,Autonomy,Consumption,Tank_capacity,Seats) VALUES('q-400',2000,82,6500,80);";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err_msg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);
}
//    sqlite3 *db;
//    char *err_msg= 0;
//    int rc;
//    string *sql = NULL;

//     rc = sqlite3_open("Airplane.db", &db);

//    if( rc ) {
//       cerr << "Can't open database:" << sqlite3_errmsg(db) << endl;
    
//    } else {
//       cout << "Opened database successfully\n";
//    }

//    // Create an SQL query 
//    *sql = "CREATE TABLE COMPANY("  \
//       "ID INT PRIMARY KEY     NOT NULL," \
//       "NAME           TEXT    NOT NULL," \
//       "AGE            INT     NOT NULL," \
//       "ADDRESS        CHAR(50)," \
//       "SALARY         REAL );";

//    /* Execute SQL statement */
//    rc = sqlite3_exec(db, sql->c_str(), callback, 0, &err_msg);
   
//    if( rc != SQLITE_OK ){
//       cerr << "SQL error: "<< err_msg;
//       sqlite3_free(err_msg);
//    } else {
//       cout << "Query ok !\n";
//    }
//    sqlite3_close(db);
//}