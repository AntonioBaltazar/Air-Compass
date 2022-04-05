#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "gamewindow.h"
#include "game.h"

using namespace std;

void Game::start() {

    GameWindow gwin("AirCompass", 4*480, 2*480);
    gwin.addRessource(Ressource("rsc/map2.bmp", 4*480, 2*480, 0, 0));
    gwin.addRessource(Ressource("rsc/mario.bmp", 120, 100, 40, 30));
    gwin.addRessource(Ressource("rsc/airplane.bmp", 48, 48, 350, 100));
    gwin.run("rsc/map.bmp");

}   