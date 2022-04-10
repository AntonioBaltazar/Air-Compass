#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "airport.h"
#include "airplane.h"
//#include "aerialnetwork.h"
#include "database.h"

struct Coord {
    int x,  y;
};

class Flight {
    private:
        int m_tick = 0;
        Airplane m_airplane;
        Edge m_edge;
        int m_color;
    public:
        Flight() {}
        Flight(Airplane _airplane, Edge _edge) : m_airplane(_airplane), m_edge(_edge) {}
        ~Flight() {}
        Airplane& get_airplane() { return m_airplane; }
        Edge& get_edge() { return m_edge; }
        int get_tick() const { return m_tick; }
        int get_color() const { return m_color; }
        void set_color(int _color) { m_color = _color; }
        void display(std::vector<Airport> _ap);
        void next_step();
};

class Simulation {
    private:
        std::vector<Flight> m_flights;
        Database* m_aerial_network;
        Graph* m_graph;
        bool m_running = false;
    public:
        Simulation() {}
        Simulation(Database* _aerial_network, Graph* _graph) : m_aerial_network(_aerial_network), m_graph(_graph) {
           // srand(time(NULL));
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
        bool can_flight(Edge _edge);

};

#endif // SIMULATION_H_INCLUDED