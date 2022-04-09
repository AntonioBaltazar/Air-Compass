#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "airport.h"
#include "airplane.h"
#include "aerialnetwork.h"

struct Coord {
    int x,  y;
};

class Flight {
    private:
        int m_tick = 0;
        Airplane m_airplane;
        Edge m_edge;
    public:
        Flight() {}
        Flight(Airplane _airplane, Edge _edge) : m_airplane(_airplane), m_edge(_edge) {}
        ~Flight() {}
        Airplane& get_airplane() { return m_airplane; }
        Edge& get_edge() { return m_edge; }
        int get_tick() { return m_tick; }
        void display();
        void next_step();
};

class Simulation {
    private:
        std::vector<Flight> m_flights;
        AerialNetwork* m_aerial_network;
        Graph* m_graph;
        bool m_running = false;
    public:
        Simulation() {}
        Simulation(AerialNetwork* _aerial_network, Graph* _graph) : m_aerial_network(_aerial_network), m_graph(_graph) {
            srand(time(NULL));
        }
        ~Simulation() {}
        // Getters & Setters
        bool is_running() { return m_running; }
        void set_running(bool _running) { m_running = _running; }
        std::vector<Flight>& get_flights() { return m_flights; }

        // Methods
        void next_step();
        void generate(int _nb_airplanes);
        void assign_flight();

};

#endif // SIMULATION_H_INCLUDED