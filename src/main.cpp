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

    GameWindow gwin("AirCompass", 1333, 900);
    int number;
    Airplane t;
    system("clear");
    cout << "[1] List of the plane\n";
    cout << "[2] List of the airport\n";
    cout << "[3] Start the simulation\n";
    cout << "What is your choice?\n";
    cin >> number;
    
    while( 4<=number >=1)
    {
        cout << "entre un bon chiffre"<< endl;
        cin >> number;
    }
    system("clear");
    if( number == 1)
    {

        int o=0;
        for(int i=0;i<6;i++)
        { 
            gwin.getAerialNetwork().get_fleet()[i].display();
        }
        cout << "[1] Return\n";
        cin >> o;
        while(o != 1 )
        {
            cout << " Enter a right number" << endl;
            cin >> o;
        }
        system("clear");
        if(o==1)
        {
            arnaud();
        }
        
    }
    if( number == 2)
    {
        int o=0;
        for(int i=0;i<=5;i++)
        {
            gwin.getAerialNetwork().get_airports()[i].display();
        }
        cout <<"[1] Return\n";
        cin >> o;
        
        while (o!=1)
        {
            cout << "Enter a right number"<< endl; 
            cin >> o;
        }
        
        system("clear");
        if(o==1)
        {
            
            arnaud();
        }
        
    }

    if( number == 3)
    {
        t.plane();
        t.choose_plane();
        t.aeroport();
        t.choose_airport();

    }
}

int main(int argc, char *argv[]) {

    int choice = 0;
    system("clear");
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