#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <sqlite3.h>
#include <vector>

#include "airport.h"
#include "airplane.h"
#include <string.h>

class Database{
private:
    char *m_sql_query;
    std::string m_database_path = "Database.db";
    sqlite3 *m_database;
    sqlite3_stmt * m_stmt; //Help to prepare a statement
    char* m_err_msg;
    int m_status = 0;
    int m_nb_arg_received = 0;
    char **m_value_arg_received;
    char **m_column_arg_received;
    inline static std::vector<std::string> value;

    inline static std::vector<Airplane> m_fleet;
    inline static std::vector<Airport> m_airports;

public:
    Database(char *sql_query, std::string database_path) : m_sql_query(sql_query),m_database_path(database_path) {}
    Database(char *sql_query,bool choice) : m_sql_query(sql_query){ if(choice) send_values(get_sql_query()); }
    Database() {}
    Database(bool txt) {
        if (txt) setup_txt(); //If true : we collect datas from txt files
        else { setup_db(); read(); } //If not : we collect datas form our databases
        
       // display_fleet();
        // display_airports();
    }
    ~Database() {}

    //Getters
    char* get_sql_query() { return m_sql_query; };
    std::string get_database_path()const { return m_database_path; };
    sqlite3* get_database() { return m_database; };
    char* get_err_mess()const { return m_err_msg; };
    int get_status()const { return m_status; };
    int get_nb_arg_received()const { return m_nb_arg_received; };
    char** get_value_arg_received() { return m_value_arg_received; };
    char** get_column_arg_received() { return m_column_arg_received; };
    std::vector<std::string> getValue() { return value; }; 
    std::vector<Airplane> get_fleet() { return m_fleet; }
    std::vector<Airport> get_airports() const { return m_airports; }

    //Setters
    void set_sql_query(char* query) { m_sql_query = query; };
    void set_database_path(std::string path) { m_database_path = path; };
    void set_database(sqlite3* db) { m_database = db; };
    void set_err_mess(char* msg) { m_err_msg = msg; };
    void set_status(int status) { m_status = status; };
    void set_nb_arg_received( int nb ) { m_nb_arg_received = nb; };
    void set_value_arg_received(char** value ) { m_value_arg_received = value; };
    void set_colomn_arg_received(char** column) { m_column_arg_received = column; };
    void set_fleet( std::vector<Airplane> _fleet) { m_fleet = _fleet ; };
    void set_airports( std::vector<Airport> _airports) { m_airports = _airports; };

    //Methods 

    static int read()
    {
        sqlite3* db;
        sqlite3* db2;
        std::string query = "SELECT * FROM Airplane;";
        std::string query2 = "SELECT * FROM Airport;";
        int rc, rc2;

        rc = sqlite3_open("Database.db", &db); //Open database
        if( rc ) std::cout << "Can't open database: "<< sqlite3_errmsg(db) << std::endl;
        rc = sqlite3_exec(db, query.c_str(), callback2, NULL, NULL); //SQL statement execution 
        if( rc != SQLITE_OK )    std::cout << "Error while asking Airplane's data\n";
        sqlite3_close(db);

        rc2 = sqlite3_open("Database.db", &db2); //Open database
        if( rc2 ) std::cout << "Can't open database: "<< sqlite3_errmsg(db2) << std::endl;
        rc2 = sqlite3_exec(db2, query2.c_str(), callback2, NULL, NULL); //SQL statement execution 
        if( rc2 != SQLITE_OK )    std::cout << "Error while asking Airport's data\n";
        sqlite3_close(db2);

        return 0;
    }

    static int callback(void *NotUsed, int nb_of_results, char **argument_received, char **Column_name_received){
        AirplaneType type = !strcmp(argument_received[1],"L") ? AirplaneType::Long : (!strcmp(argument_received[1],"M") ? AirplaneType::Medium : AirplaneType::Short);

        m_fleet.push_back({
            argument_received[0],  //Name
            type, //type
            atoi(argument_received[2]), //Autonomy
            atoi(argument_received[3]), //Consumption 
            atoi(argument_received[4]), //Tank capacity 
            atoi(argument_received[5])  //Number of seats
        });    

        return 0;
    }

    static int callback2(void *NotUsed, int nb_of_results, char **argument_received, char **Column_name_received){
        m_airports.push_back({
            argument_received[0], //Name
            argument_received[1], //Location
            {strtod(argument_received[2],NULL),strtod(argument_received[3],NULL)}, //GPS (lattitude , longitude)
            atoi(argument_received[4]), //Number of runaways
            atoi(argument_received[5]), //Number of parking spots
            atoi(argument_received[6]), //Delay between flight
            atoi(argument_received[7]), //Standby flight time
            atoi(argument_received[8]), //Delay parking to runaway
            atoi(argument_received[9]), //Delay landing
            atoi(argument_received[10]), //Delay anticolision
            atoi(argument_received[11]), //Aeroport's postition on x-axis
            atoi(argument_received[12]), //Aeroport's postition on y-axis
        });
        return 0;
    }

    void display_fleet();
    void display_airports();
    void setup_txt();
    void create_fleet_txt_file();
    void setup_db();
    void send_values(char* query);
    void send_values();
};


#endif // DATABASE_H_INCLUDED