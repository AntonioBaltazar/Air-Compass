#include <iostream>
#include <vector>
#include "airplane.h"
#include "airport.h"
#include "graph.h"
#include "graphreader.h"

using namespace std;
using namespace GraphReader;

int main(int argc, char *argv[]) {
    
    vector<Airplane> bank;

    bank=read_plane();
    
    for(int i=0; i<6;i++)
        bank[i].display();
    
    GraphReader::test();
    Graph g;
    GraphReader::load_graph("graph.txt", g);
    return 0;
}