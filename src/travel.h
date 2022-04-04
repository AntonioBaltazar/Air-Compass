#ifndef TRAJET_H_INCLUDED
#define TRAJET_H_INCLUDED

#include "airport.h"

class Travel
{
private:
    int m_distance;
    int m_id;
    
    Airport* m_destination;
    Airport* m_start;

public:
    // Constructors & Destructor
    Travel() {};
    ~Travel() {};

    // Getters
    int get_distance() const { return m_distance; }
    Airport* get_destination() { return m_destination; }
    Airport* get_start() { return m_start; }
    int get_id() const { return m_id ; };

    //Setters
    void set_id(int _id) { m_id = _id ; };

    

};

#endif