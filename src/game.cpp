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
    gwin.addRessource(Ressource("rsc/airport.gif", 63, 48, 400, 600));
   
    gwin.run("rsc/map.bmp");

}   