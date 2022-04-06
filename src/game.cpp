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
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 672, 357));
    // New York
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 346, 400));
    // Sydney
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 1279, 760));
    //Shanghai
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 1160, 446));
    // Johannesbourg
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 775, 700));
    // Sao Paulo
    gwin.addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 469, 705));
   
    gwin.run("rsc/map.bmp");

}   