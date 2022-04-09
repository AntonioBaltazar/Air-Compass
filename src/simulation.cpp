#include <iostream>
#include <vector>
#include "graph.h"
#include "simulation.h"
#include "gamewindow.h"


using namespace std;

void Flight::next_step() { m_tick++; }

void Simulation::assign_flight() {
    Airplane r_airplane = m_aerial_network->get_fleet()[5];
    //m_aerial_network->get_fleet()[rand() % m_aerial_network->get_fleet().size()];
    Graph temp = *m_graph;
    temp.limitEdge(r_airplane.get_autonomy());
   // m_graph->display_graph();
    vector<Edge> edges = temp.get_edges();
    Edge r_edge = edges[rand() % edges.size()];
    //SDL_Log(string("DEBUG"+edges.size()).c_str());
    m_flights.push_back(Flight(r_airplane, r_edge));
}

void Simulation::next_step() {
    for (auto i = m_flights.begin(); i != m_flights.end(); ++i) {
        if ((*i).get_tick() <= (*i).get_edge().weigth) {
            if ((*i).get_tick() == (*i).get_edge().weigth) {
                SDL_Log("DEBUG");
                m_flights.erase(i--);
                assign_flight();
            } else {
            (*i).next_step();
            (*i).display();
            }
        } else {
            SDL_Log("DEBUG");
            m_flights.erase(i--);
            assign_flight();
        } 
    }
}

void Simulation::generate(int _nb_airplanes) {
    m_flights.clear();
    for (int i = 0; i < _nb_airplanes; i++) 
        assign_flight();
    for (auto& el : m_flights)
        el.display();
    m_running = true;
}   

void Flight::display() {
    AerialNetwork an;
    an.create_fleet();
    SDL_Log((an.get_airports()[m_edge.src].get_city() + "  --> " + an.get_airports()[m_edge.dest].get_city()).c_str());
    float pourcent = (float)m_tick/m_edge.weigth;
    SDL_Log((string(50*pourcent, '#') + string(50 - 50*pourcent, '-') + "\n\n").c_str());
}