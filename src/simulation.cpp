#include <iostream>
#include "simulation.h"

void Flight::next_step() { m_tick++; }

void Simulation::next_step() {
    for (auto& flight : m_flights) {
        flight.next_step();
    }
}

void Simulation::generate(int _nb_airplanes) {

    m_flights.clear();
    for (int i = 0; i < _nb_airplanes; i ++) {
        
    }

}