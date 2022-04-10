#ifndef HANDLE_TERMINAL_H_INCLUDED
#define HANDLE_TERMINAL_H_INCLUDED

#include <iostream>
#include "graph.h"
#include "database.h"

class Terminal {
private:
    Database m_database = Database(true);
    std::vector<Airport> m_airports;
    Airport m_dep, m_end;
    Airplane m_airplane;
    
public: 
    Terminal() {
        Database db(true);
        db.display_airports();
       m_airports = db.get_airports();

       terminal_menu();
    }
    ~Terminal() {}
    int terminal_menu();
    void terminal_mode();
    void clear_screen();
    void airport_choice();
    Airport airport_choice(Airport* without, std::string str);
    Airplane airplane_choice();
};

#endif // HANDLE_TERMINAL_INCLUDED