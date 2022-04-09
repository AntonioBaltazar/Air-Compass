#ifndef AIRPLANE_H_INCLUDED
#define AIRPLANE_H_INCLUDED

#include "airport.h"
#include <iostream>

enum class AirplaneType { Short, Medium, Long };

class Airplane {
private:
    std::string m_name;
    AirplaneType m_type;
    int m_consumption;
    int m_fuel_capacity;
    int m_autonomy;
    int m_nb_seats;
    Airport m_current_airport;
    Airport m_start;
    Airport m_destination;


public:
    // Constructors & Destructor
    Airplane() {}
    Airplane(std::string name, AirplaneType type, int autonomy, int consumption,  int fuel_capacity, int nb_seats)
    : m_name(name), m_type(type), m_consumption(consumption), m_fuel_capacity(fuel_capacity), m_autonomy(autonomy), m_nb_seats(nb_seats) {}
    ~Airplane() {}

    // Getters
    std::string get_name() const { return m_name; }
    AirplaneType get_type() const { return m_type; }
    int get_consumption() const { return m_consumption; }
    int get_fuel_capacity() const { return m_fuel_capacity; }
    int get_autonomy() const { return m_autonomy; }
    int get_nb_seats() const { return m_nb_seats; }
    Airport get_current_airport() const { return m_current_airport; } 
    Airport get_destination() const { return m_destination ; }

    // Setters
    void set_name(std::string _name) { m_name = _name; }
    void set_type(AirplaneType _type) { m_type = _type; }
    void set_consumption(int _consumption) { m_consumption = _consumption; }
    void set_fuel_capacity(int _fuel_capacity) { m_fuel_capacity = _fuel_capacity; }
    void set_autonomy(int _autonomy) { m_autonomy = _autonomy; }
    void set_nb_seats(int _nb_seats) { m_nb_seats = _nb_seats; }
    void set_current_airport(Airport _current_airport) { m_current_airport = _current_airport; }

    // Methods
    void display();
    void choose_plane();
    void plane();
    void aeroport();
    void choose_airport();
};

#endif // AIRPLANE_H_INCLUDED