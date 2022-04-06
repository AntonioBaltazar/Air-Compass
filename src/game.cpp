#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "gamewindow.h"
#include "game.h"

using namespace std;

void Game::start() {

    GameWindow gwin("AirCompass", 1333, 900);   
    gwin.run("rsc/map.bmp");

}   