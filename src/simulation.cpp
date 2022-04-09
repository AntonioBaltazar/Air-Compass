#include <iostream>
#include <vector>
#include <random>
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
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, edges.size() - 1); // distribution in range [1, 6]
    int r = dist6(rng);
    Edge r_edge = edges[r];
    SDL_Log("%d \n", r);
    
    //SDL_Log(string("DEBUG"+edges.size()).c_str());

    m_flights.push_back(Flight(r_airplane, r_edge));
}

void Simulation::next_step() {
    
    int count = 0;
    for (auto i = m_flights.begin(); i != m_flights.end(); ++i) {
        if ((*i).get_tick() >= (*i).get_edge().weigth) {
            //SDL_Log("FINISHED");
            m_flights.erase(i--);
            int t = (*i).get_edge().src + 1;
            
            assign_flight();
        } else {
            (*i).next_step();
            //(*i).display();
        }/* 
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
        }  */
        count++;
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