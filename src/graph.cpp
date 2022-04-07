#include <iostream>
#include "graph.h"

using namespace std;

void Vertice::display() {
    cout << "[Vertice " << get_number() << "]\n";
    cout << get_airport().get_name() << " | [?] " << get_airport().get_city();
    cout << " (" << get_airport().get_location().latitude << ":" << get_airport().get_location().longtitude << ")\n";

    cout << "Distance as the crow flies\n";
    for (const auto& _adj : get_adjacent()) {
        cout << "  " << _adj.second*200 << "km to " << _adj.first->get_airport().get_city() << "\n";
    }
    cout << "\n";
}

void Graph::display() {
    cout << "\n\nAirCompass :\n\n";
    for (auto& _vertice : get_vertices())
        _vertice.display();
}
