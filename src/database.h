#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <sqlite3.h>

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

    public:
        Database(char *sql_query, std::string database_path) : m_sql_query(sql_query),m_database_path(database_path) {};
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
        


};

static int callback(void *NotUsed, int argc, char **argv, char **azColName);
void setup_db();
void  handle_db_plane();
void  create_db_plane();

#endif // DATABASE_H_INCLUDED