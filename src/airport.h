#ifndef AIRPORT_H_INCLUDED
#define AIRPORT_H_INCLUDED

#include <iostream>

struct GPS {
    double latitude;
    double longtitude;
};

class Airport {
    private:
        std::string m_name, m_city;
        GPS m_location;
        int m_nb_runway, m_nb_parking, m_delay_between_flights, m_standby_flight_time, m_delay_parking_to_runway, m_delay_landing, m_delay_anticollision;
    public:
        // Constructors & Destructor
        Airport() {}
        ~Airport() {}

        // Getters
        std::string get_name() const { return m_name; }
        std::string get_city() const { return m_city; }
        GPS& get_location() { return m_location; }
        int get_nb_runway() const { return m_nb_runway; }
        int get_nb_parking() const { return m_nb_parking; }
        int get_delay_between_flights() const { return m_delay_between_flights; }
        int get_standby_flight_time() const { return m_standby_flight_time; }
        int get_delay_parking_to_runway() const { return m_delay_parking_to_runway; }
        int get_delay_landing() const { return m_delay_landing; }
        int get_delay_anticollision() const { return m_delay_anticollision; }

        // Setters
        void set_name(std::string _name) { m_name = _name; }
        void set_city(std::string _city) { m_city = _city; }
        void set_nb_runway(int _nb_runway) { m_nb_runway = _nb_runway; }
        void set_nb_parking(int _nb_parking) { m_nb_parking = _nb_parking; }
        void set_delay_between_flights(int _delay_between_flights) { m_delay_between_flights = _delay_between_flights; }
        void set_standby_flight_time(int _standby_flight_time) { m_standby_flight_time = _standby_flight_time; }
        void set_delay_parking_to_runway(int _delay_parking_to_runway) { m_delay_parking_to_runway = _delay_parking_to_runway; }
        void set_delay_landing(int _delay_landing) { m_delay_landing = _delay_landing; }
        void set_delay_anticollision(int _delay_anticollision) { m_delay_anticollision = _delay_anticollision; }
};

#endif // AIRPORT_H_INCLUDED