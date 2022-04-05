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
     SDL_Surface* image = IMG_Load("rsc/map.bmp");
     SDL_Surface* image2 = IMG_Load("rsc/mario.bmp");
    if (!init()) printf("Failed to initialize!\n");
    else {
        //SDL_BlitSurface(image, NULL, getSurface(), NULL);
        SDL_UpdateWindowSurface(getWindow());
    }
    
    Ressource rsc1("rsc/map.bmp", 2*480, 480, 0, 0);
    Ressource rsc2("rsc/mario.bmp", 2*480, 480, 0, 0);
    SDL_Rect src1{0, 0, 0, 0};
    SDL_Rect dst1{ 0, 0, 400, 300 };
    SDL_Rect src2{ 0, 0, 0, 0 };
    SDL_Rect dst2{ getWidth()- 240, getHeight() - 100, 240, 100};
    src2.x = src1.w / 2 - 30;
    src2.y = src1.h / 2 - 50;
    src2.w = 50;
    src2.h = 50;

   
    SDL_Texture* t1 = SDL_CreateTextureFromSurface(getRender(), image);
    SDL_Texture* t2 = SDL_CreateTextureFromSurface(getRender(), image2);
    SDL_FreeSurface(image);

    SDL_QueryTexture(t1, nullptr, nullptr, &src1.w, &src1.h);
    //SDL_QueryTexture(t1, nullptr, nullptr, &src1.w, &src1.h);

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
        SDL_SetRenderDrawColor(getRender(), 0, 0, 0, 255); 
        SDL_RenderClear(getRender());

        SDL_RenderCopy(getRender(), t1, NULL, NULL);
        SDL_RenderCopy(getRender(), t2, NULL, &dst2);

        SDL_RenderPresent(getRender());  
 
    }
    close();
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