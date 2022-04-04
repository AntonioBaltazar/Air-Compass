#include <iostream>
#include <vector>
#include "airplane.h"
#include "airport.h"
#include "graph.h"
#include "graphreader.h"

using namespace std;
using namespace GraphReader;

int main(int argc, char *argv[]) {
    
    vector<Airplane> test;

    test=read_plane();
    
    // for(int i=0; i<6;i++)
    //     test[i].display();
    
    GraphReader::test();
    return 0;
}