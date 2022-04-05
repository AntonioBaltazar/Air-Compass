#include <iostream>
#include <SDL2/SDL.h>
#include "gamewindow.h"

using namespace std;

bool GameWindow::init() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return false;
	} 

    //Create window
    setWindow(SDL_CreateWindow(getWindowName().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, getWidth(), getHeight(), SDL_WINDOW_SHOWN ));
    if(getWindow() == NULL ) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    
    //Get window surface
    setSurface(SDL_GetWindowSurface(getWindow()));
    return true;
}

bool GameWindow::loadMedia(std::string _path_image) {
    setImage(SDL_LoadBMP(_path_image.c_str()));
    return getImage() != nullptr;
}

bool GameWindow::close() {
    SDL_FreeSurface(getImage());
    setImage(NULL);
    SDL_DestroyWindow(getWindow());
    setWindow(NULL);
    SDL_Quit();
}

void GameWindow::run(std::string _path_image) {
    if (!init()) printf("Failed to initialize!\n");
    else {
        if (!loadMedia(_path_image)) printf("Failed to load media!\n");
        else {
            SDL_BlitSurface(getImage(), NULL, getSurface(), NULL);
            SDL_UpdateWindowSurface(getWindow());
        }
    }

    SDL_Event events;
    bool isOpen{true};
    while (isOpen) {
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT:
                        isOpen = false;
                    break;
                default: break;
            }
        }
    }
    close();
}