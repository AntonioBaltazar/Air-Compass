#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <sqlite3.h>
#include <vector>

class Database{
    private:
        char *m_sql_query;
        std::string m_database_path = "Database.db";
        sqlite3 *m_database;
        char m_err_msg;
        int m_status = 0;
        int m_nb_arg_received = 0;
        char **m_value_arg_received;
        char **m_column_arg_received;
        inline static std::vector<std::string> value;

    public:
        Database(char *sql_query, std::string database_path) : m_sql_query(sql_query),m_database_path(database_path) {};
        Database() {};
        ~Database() {};

        //Getters
        char* get_sql_query() { return m_sql_query; };
        std::string get_database_path()const { return m_database_path; };
        sqlite3* get_database() { return m_database; };
        char get_err_mess()const { return m_err_msg; };
        int get_status()const { return m_status; };
        int get_nb_arg_received()const { return m_nb_arg_received; };
        char** get_value_arg_received() { return m_value_arg_received; };
        char** get_column_arg_received() { return m_column_arg_received; };
        std::vector<std::string> getValue() { return value; }; 
    
        //Setters
        void set_sql_query(char* query) { m_sql_query = query; };
        void set_database_path(std::string path) { m_database_path = path; };
        void set_database(sqlite3* db) { m_database = db; };
        void set_err_mess(char msg) { m_err_msg = msg; };
        void set_status(int status) { m_status = status; };
        void set_nb_arg_received( int nb ) { m_nb_arg_received = nb; };
        void set_value_arg_received(char** value ) { m_value_arg_received = value; };
        void set_colomn_arg_received(char** column) { m_column_arg_received = column; };

        //Methods 

        static int read()
        {
            sqlite3* db;
            std::string query = "SELECT NAME FROM Airplane;";
            std::string query2 = "SELECT NAME FROM Airport;";
            char* err_msg;
            int rc;

            rc = sqlite3_open("Database.db", &db); /* Open database */
            
            if( rc ) 
                std::cout << "Can't open database: "<< sqlite3_errmsg(db) << std::endl;
            else 
                std::cout << "Opened database successfully\n";

            /* Execute SQL statement */
            rc = sqlite3_exec(db, query.c_str(), callback, 0, &err_msg);
            
            if( rc != SQLITE_OK ){
                std::cout << "SQL error: " << err_msg;
                sqlite3_free(err_msg);
            } else 
                std::cout << "Table created successfully\n";

            sqlite3_close(db);
        }

        static int callback(void *NotUsed, int nb_of_results, char **argument_received, char **Column_name_received){
            for(int i = 0; i < nb_of_results; i++)        
                value.push_back(argument_received[i]);  // Show column name, value, and newline

            // Return successful
            return 0;
        }

        void display() {   
            std::cout << "GOOOOO\n";          
            for(auto& el:getValue())
                std::cout << el << "\n";
        }

    void setup_db();

};


#endif // DATABASE_H_INCLUDED