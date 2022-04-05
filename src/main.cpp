#include <iostream>
#include <vector>
#include "airplane.h"
#include "airport.h"
#include "graph.h"
#include "graphreader.h"
#include "aerialnetwork.h"
#include "travel.h"
#include <ncurses.h>

using namespace std;
using namespace GraphReader;

void antonio() {
    AerialNetwork test;
    test.create_fleet();
    for (int i = 0; i < 5; i++)
        test.get_fleet()[i].display();
}

void martin() {
    Graph g;
    GraphReader::load_graph("graph.txt", g);
    g.display();
}

void arnaud() {

}

int main(int argc, char *argv[]) {

    while(1) {
        cout << "\n\n\nAirCompass : \n[1] Tonio\n[2] Martin\n[3] Arnaud\n[4] Quitter";
        int c = getc(stdin);

        switch(c) {
            case 49:
                antonio();
                break;
            case 50:
                martin();
                break;
            case 51:
                arnaud();
                break;
            case 52:
                return 0;
            default: break;
        }
    }

    return 0;
}