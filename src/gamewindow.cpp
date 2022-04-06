#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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

void GameWindow::close() {
    for (auto& el : getRessources())
        SDL_FreeSurface(el.getSurface());
    SDL_DestroyWindow(getWindow());
    setWindow(NULL);
    SDL_Quit();
}

void GameWindow::updateTextures() {
    
    getTextures().clear();
    for (auto& el : getRessources())
        getTextures().push_back(make_pair(SDL_CreateTextureFromSurface(getRender(), el.getSurface()), 
            SDL_Rect{el.getRelativeX(), el.getRelativeY(), el.getWidth(), el.getHeight()}));
}

void GameWindow::updateTexture(std::string _path) {
    Ressource* tmp = NULL;
    int i = 0;
    for (auto& el : getRessources()) 
        if (el.getPath() == _path) {
            tmp = &el;
            i++;
        }
    if (tmp == NULL) return;
    getTextures()[i] = make_pair(SDL_CreateTextureFromSurface(getRender(), tmp->getSurface()), 
            SDL_Rect{tmp->getRelativeX(), tmp->getRelativeY(), tmp->getWidth(), tmp->getHeight()});
}

void GameWindow::menu()
{
    if(!init()) cout << "Failed to initialize !\n";
    else  SDL_UpdateWindowSurface(getWindow());
    int choice = 0;
    
    addRessource(Ressource("rsc/menu.jpg",Display::TOP_LEFT, 1333, 900, 0, 0, false));
    addRessource(Ressource("rsc/cursor.png",Display::CENTER, 37, 30, 300, 400, false));

    updateTextures();
    
    // Events managing
    SDL_Event events;
    bool open{true};
    while (open) {
        while (SDL_PollEvent(&events)) {
            if(choice > 4) choice = 0;
            if(choice < 0) choice = 4;
            switch (events.type) {
                
                case SDL_QUIT:        // If window's closed we quit sdl mode 
                    open = false;
                    break;

                case SDL_KEYDOWN:     // Key has been pressed  
                    // If it's escape key then we also quit sdl mode
                    if(events.key.keysym.scancode == SDL_SCANCODE_ESCAPE) open = SDL_FALSE;
                    
                    if(events.key.keysym.scancode == SDL_SCANCODE_UP && choice > 0) {
                        cursor_move(choice);
                        choice--;
                    }
                    
                    if(events.key.keysym.scancode == SDL_SCANCODE_DOWN && choice < 4){
                        cursor_move(choice);
                        choice++;
                    } 
                    
                    break;

                default: break;

            }
                SDL_Log("Choice = %d",choice);
        }

        SDL_SetRenderDrawColor(getRender(), 0, 0, 0, 255); 
        SDL_RenderClear(getRender());

         for (auto& el : getTextures())
            SDL_RenderCopy(getRender(), el.first, NULL, &el.second);

        SDL_RenderPresent(getRender());  //Display's images
    }
    close();

}

void GameWindow::cursor_move(int choice){
    if(choice == 1)
        m_ressources[1].setY(480);
    if(choice == 2)
        m_ressources[1].setY(560);
    if(choice == 3)
        m_ressources[1].setY(640);
    updateTexture("rsc/cursor.png");
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