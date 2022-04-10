#include <iostream>
#include <vector>
#include <random>
#include "graph.h"
#include "simulation.h"
#include "gamewindow.h"

using namespace std;

void Flight::next_step() { m_tick++; }

bool Simulation::can_flight(Edge _edge) {
    for (auto& flight : m_flights) {
        if (flight.get_edge().src == _edge.dest && flight.get_edge().dest == _edge.src) 
            return false;
    }
    return true;
}

void Simulation::assign_flight() {
    Airplane r_airplane = m_aerial_network->get_fleet()[5];

    Graph temp = *m_graph;
    temp.limitEdge(r_airplane.get_autonomy());

    vector<Edge> edges = temp.get_edges();
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, edges.size() - 1); // distribution in range [1, 6]
    std::uniform_int_distribution<std::mt19937::result_type> dist5(1, 5);
    Edge r_edge;
    do {
        r_edge = edges[dist6(rng)];
    } while(!can_flight(r_edge));

    Flight t_flight = Flight(r_airplane, r_edge);
    t_flight.set_color(dist5(rng));
    m_flights.push_back(t_flight);
}

void Simulation::next_step() {

    for (auto i = m_flights.begin(); i != m_flights.end(); ++i) {
        if ((*i).get_tick() >= (*i).get_edge().weigth) {
            //SDL_Log("FINISHED");
            m_flights.erase(i--);
            int t = (*i).get_edge().src + 1;
            
            assign_flight();
        } else {
            (*i).next_step();
            (*i).display(m_aerial_network->get_airports());
        }
    }
}

void Simulation::generate(int _nb_airplanes) {
    m_flights.clear();
    for (int i = 0; i < _nb_airplanes; i++) 
        assign_flight();
    for (auto& el : m_flights)
        el.display(m_aerial_network->get_airports());
    m_running = true;
}   

void Flight::display(vector<Airport> _ap) {
    SDL_Log((_ap[m_edge.src].get_city() + "  --> " + _ap[m_edge.dest].get_city()).c_str());
    float pourcent = (float)m_tick/m_edge.weigth;
    SDL_Log((string(50*pourcent, '#') + string(50 - 50*pourcent, '-') + "\n\n").c_str());
}