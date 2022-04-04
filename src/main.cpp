#include <iostream>
#include <vector>
#include "airplane.h"
#include "airport.h"
#include "graph.h"
#include "graphreader.h"
#include "aerialnetwork.h"
#include "travel.h"

using namespace std;
using namespace GraphReader;

int main(int argc, char *argv[]) {
    
    AerialNetwork test;
    
    test.create_fleet();
   

    for (int i = 0; i < 5; i++)
        test.get_fleet()[i].display();
    
    
    return 0;
}