#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "gamewindow.h"
#include "game.h"

using namespace std;

void Game::start() {

    GameWindow gwin("AirCompass", 1333, 900);

    gwin.addRessource(Ressource("rsc/realmap.jpg", 1333, 900, 0, 0));

    // Paris
    gwin.addRessource(Ressource("rsc/airport.gif", 63, 48, 672 - 63/2, 357 - 48/2));
    // New York
    gwin.addRessource(Ressource("rsc/airport.gif", 63, 48, 346 - 63/2, 400 - 48/2));
    // Sydney
    gwin.addRessource(Ressource("rsc/airport.gif", 63, 48, 1279 - 63/2, 760 - 48/2));
    //Shanghai
    gwin.addRessource(Ressource("rsc/airport.gif", 63, 48, 1160 - 63/2, 446 - 48/2));
    // Johannesbourg
    gwin.addRessource(Ressource("rsc/airport.gif", 63, 48, 775 - 63/2, 700 - 48/2));
    // Sao Paulo
    gwin.addRessource(Ressource("rsc/airport.gif", 63, 48, 469 - 63/2, 705 - 48/2));
   
    gwin.run("rsc/map.bmp");

}   