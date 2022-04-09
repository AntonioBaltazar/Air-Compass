#include <iostream>
#include <vector>
#include "graph.h"
#include "simulation.h"
#include "gamewindow.h"

using namespace std;

void Flight::next_step() { m_tick++; }

void Simulation::next_step() {
    for (auto& flight : m_flights) {
        flight.next_step();
    }
}

void Simulation::generate(int _nb_airplanes) {
    m_flights.clear();
    // Pour chaque avion, on va chercher un aéroport dans lequel un trajet est possible en fct de l'avion
    // Puis on assigne ce trajet
    // Quand trajet est finit on en cherche un autre depuis l'aéroport
    
    for (int i = 0; i < _nb_airplanes; i++) {
        Airplane r_airplane = m_aerial_network->get_fleet()[rand() % m_aerial_network->get_fleet().size()];
        Graph temp = *m_graph;
        temp.limitEdge(r_airplane.get_autonomy());
        vector<Edge> edges = temp.get_edges();

        Edge r_edge = edges[rand() % edges.size()];
        m_flights.push_back(Flight(r_airplane, r_edge));

       /*  bool airport_valid = false;
        while (!airport_valid) {
            int r = rand() % m_aerial_network->get_airports().size();
            for (auto& adj : m_aerial_network->get_airports()[r]) {
                // Mettre voisins aléatoire plus tard
                
            }
        } */

    }
    for (auto& el : m_flights)
        el.display();
/* 
    for (int i = 0; i < _nb_airplanes; i ++) {
        for (m_aerial_network->get_airports())
    } */
    m_running = true;
}   

void Flight::display() {
    AerialNetwork an;
    an.create_fleet();
    SDL_Log((an.get_airports()[m_edge.src].get_city() + "  --> " + an.get_airports()[m_edge.dest].get_city()).c_str());
    float pourcent = (float)m_tick/m_edge.weigth;
    SDL_Log((string(50*pourcent, '#') + string(50 - 50*pourcent, '-') + "\n\n").c_str());
}