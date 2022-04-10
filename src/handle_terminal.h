#ifndef HANDLE_TERMINAL_H_INCLUDED
#define HANDLE_TERMINAL_H_INCLUDED

#include "airport.h"
#include "database.h"

class Terminal {
private:
    Database m_database = Database(true);
public: 
    Terminal() {
        terminal_menu();
    }
    ~Terminal() {}
    int terminal_menu();
    void terminal_mode();
    void clear_screen();
    void airport_choice();
    Airport airport_choice(Airport* without, std::string str);
};

#endif // HANDLE_TERMINAL_INCLUDED