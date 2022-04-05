#include <iostream>
#include <SDL2/SDL.h>
#include "graphicelement.h"

using namespace std;

bool mouse_coordinates(SDL_Event event, int x1, int x2, int y1, int y2)
{
    if( event.motion.x > x1 && event.motion.x < x2 && event.motion.y > y1 && event.motion.y < x2 )  return true;
    else return false;
}

void handle_event()
{
    SDL_Event events; 
    SDL_bool run = SDL_TRUE;
    SDL_Renderer *renderer = NULL;
    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                          SDL_WINDOWPOS_UNDEFINED,
                                                          640,
                                                          480,
                                                          SDL_WINDOW_SHOWN);

    while (run) {
        while (SDL_PollEvent(&events)) {    //non-blocking event
            switch(events.type){
                
                case SDL_WINDOWEVENT:   //Window event 
                    if (events.window.event == SDL_WINDOWEVENT_CLOSE) //Window closing allowermeture de la fenetre permet de sortir de la boucle
                        run = SDL_FALSE;
                    break;

                case SDL_KEYDOWN: {     //Key has been pressed  
                    if(events.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                        run = SDL_FALSE;
                    break;
                    
                case SDL_MOUSEMOTION:
                    // SDL_Log("Mouvement de souris (%d %d) (%d %d)", events.motion.x, events.motion.y, events.motion.xrel, events.motion.yrel);
                    if(mouse_coordinates(events,50,100,10,15)) SDL_Log("On y est !");
                    else SDL_Log("On n'y est pas...");
                    break;

                case SDL_MOUSEWHEEL: //Mouse wheel up and down 
                    if (events.wheel.y > 0)
                        SDL_Log("up %d", events.wheel.y);
                    else if (events.wheel.y < 0) 
                         SDL_Log("down %d", events.wheel.y);
                    break;
                }

            }
        }       
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}

