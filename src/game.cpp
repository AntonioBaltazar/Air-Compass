#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "gamewindow.h"
#include "game.h"

using namespace std;

void Game::start() {

    GameWindow gwin("AirCompass", 1333, 900);

    gwin.addRessource(Ressource("rsc/realmap.jpg", Display::TOP_LEFT, 1333, 900, 0, 0, false));

    // Paris
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 639, 329));
    // New York
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 315, 376));
    // Sydney
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 1248, 736));
    //Shanghai
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 1129, 422));
    // Johannesbourg
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 744, 676));
    // Sao Paulo
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 438, 681));
   
    gwin.run("rsc/map.bmp");

}   