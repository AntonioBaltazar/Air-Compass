#ifndef AERIALNETWORK_H_INCLUDED
#define AERIALNETWORK_H_INCLUDED

#include <vector>
#include "airplane.h"
#include "airport.h"
#include "travel.h"

class AerialNetwork{
    private:
        std::vector<Airplane> m_fleet;
        std::vector<Airport> m_airports;
        std::vector<Travel> m_travel_book;

    public:

        //Constructor 
        AerialNetwork() {};
        ~AerialNetwork() {};
        
        //Getters
        std::vector<Airplane> get_fleet() const { return m_fleet ; };
        std::vector<Airport> get_airports() const { return m_airports ; };
        std::vector<Travel> get_travel_book() const { return m_travel_book ; };
    
        //Setters
        void set_fleet( std::vector<Airplane> _fleet) { m_fleet = _fleet ; };
        void set_airports( std::vector<Airport> _airports) { m_airports = _airports; };
    
        //Methods
        void create_fleet();
        
};

#endif // AERIALNETWORK_H_INCLUDED