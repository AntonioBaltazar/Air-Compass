#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "airport.h"
#include "airplane.h"

class Flight {
    private:
        int m_tick;
        Airplane m_airplane;
        Airport m_src, m_dest;
    public:
        Flight() {}
        ~Flight() {}
        void next_step();
};

class Simulation {
    private:
        std::vector<Flight> m_flights;
        bool m_running = false;
    public:
        Simulation() {}
        ~Simulation() {}

        bool is_running() { return m_running; }
        void set_running(bool _running) { m_running = _running; }
        // Methods
        void next_step();
        void generate(int _nb_airplanes);

};

#endif // SIMULATION_H_INCLUDED