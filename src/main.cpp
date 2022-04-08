#include <iostream>
#include <vector>
#include <ncurses.h>
#include <SDL2/SDL_ttf.h>
#include "airplane.h"
#include "airport.h"
#include "graph.h"
#include "graphreader.h"
#include "aerialnetwork.h"
#include "travel.h"
#include "game.h"
#include "graphicelement.h"
#include "gamewindow.h"
#include "database.h"

using namespace std;
using namespace GraphReader;

void antonio() {
    GameWindow menu("AirCompass", 1333, 900);
    // create_db_plane();
    //setup_db();
    menu.menu();
}

void martin() {
    Game g;
    g.start();
    /*Graph g("graph.txt");
    g.display_graph();
    //g.primMST(Vertice(0));
    g.shortest_path(Vertice(0));
   */
}

void arnaud() {
    Airplane t;
    t.choose();

}

int main(int argc, char *argv[]) {

    int choice = 0;

    do
    {
        cout << "\n\n\nAirCompass : \n[1] Tonio\n[2] Martin\n[3] Arnaud\n[4] Quitter\n ->";
        cin >> choice;
        switch(choice) {
            case 1:
                antonio();
                break;
            case 2:
                martin();
                break;
            case 3:
                arnaud();
                break;
            case 4:
                return 0;
            default: break;
        }
    } while (choice == 0);

    return 0;
}