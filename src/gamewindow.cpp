#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gamewindow.h"

using namespace std;

void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);

bool GameWindow::init() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return false;
	} 

    //Create window
    SDL_Window* win{ nullptr };
    SDL_Renderer* rend{ nullptr };
    SDL_CreateWindowAndRenderer(getWidth(), getHeight(), SDL_WINDOW_SHOWN, &win, &rend);
    setRender(rend);
    setWindow(win);
    if(getWindow() == NULL ) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    
    return true;
}

bool GameWindow::close() {
    SDL_DestroyWindow(getWindow());
    setWindow(NULL);
    SDL_Quit();
}

void GameWindow::run(std::string _path_image) {
    if (!init()) printf("Failed to initialize!\n");
    else
        SDL_UpdateWindowSurface(getWindow());
    
    vector<pair<SDL_Texture*, SDL_Rect>> textures;
    for (auto& el : getRessources()) {
        textures.push_back(make_pair(SDL_CreateTextureFromSurface(getRender(), el.getSurface()), 
            SDL_Rect{el.getRelativeX(), el.getRelativeY(), el.getWidth(), el.getHeight()}));
        SDL_FreeSurface(el.getSurface());
    }

    SDL_Event events;
    bool isOpen{true};
    while (isOpen) {
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT:
                    isOpen = false;
                    break;
                case SDL_MOUSEMOTION:
                    //SDL_Log("Mouvement de souris (%d %d) (%d %d)", events.motion.x, events.motion.y, events.motion.xrel, events.motion.yrel);
                    if (isRessourceClicked(events.motion.x, events.motion.y)) 
                        SDL_Log("Element surpasse");
                    else
                        SDL_Log("rien");
                    //if(mouse_coordinates(events,50,100,10,15)) SDL_Log("On y est !");
                    //else SDL_Log("On n'y est pas...");
                    break;

                default: break;
            }
        }
        
        SDL_SetRenderDrawColor(getRender(), 0, 0, 0, 255); 
        SDL_RenderClear(getRender());

        // Appending differents ressources
        for (auto& el : textures)
            SDL_RenderCopy(getRender(), el.first, NULL, &el.second);

        SDL_RenderPresent(getRender());  
 
    }
    close();
}

bool GameWindow::isRessourceClicked(int _x, int _y) {
    for (auto& el : getRessources())
        if (el.isClickable())
            if (_x >= el.getRelativeX() && _x < el.getRelativeX() + el.getWidth() && _y >= el.getRelativeY() && _y < el.getRelativeY() + el.getHeight())
                return true;
    return false;
}

void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius) { 
    const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}