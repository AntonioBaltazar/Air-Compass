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
        if (!el.isRenderable()) continue;
        else if (el.getElement() == Element::IMAGE)
            getTextures().push_back(make_pair(SDL_CreateTextureFromSurface(getRender(), el.getSurface()), 
                SDL_Rect{el.getRelativeX(), el.getRelativeY(), el.getWidth(), el.getHeight()}));
        else if (el.getElement() == Element::TEXT || el.getElement() == Element::SELECTOR_AIRPLANE || el.getElement() == Element::SELECTOR_AIRPORT)
            getTextures().push_back(make_pair(SDL_CreateTextureFromSurface(getRender(), el.getSurface()), 
                SDL_Rect{el.getRelativeX(), el.getRelativeY(), el.getSurface()->w, el.getSurface()->h}));
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
    else SDL_UpdateWindowSurface(getWindow());
    
    addRessource(Ressource("rsc/realmap.jpg", Display::TOP_LEFT, 1333, 900, 0, 0, false));
    // Paris | New York | Sydney | Shanghai | Johannesbourg | Sao Paulo 
    addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 639, 329));
    addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 315, 376));
    addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 1248, 736));
    addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 1129, 422));
    addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 744, 676));
    addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, 438, 681));

    // Text
    cout << "deb";
    addRessource(Ressource("Selectionner un avion", Display::TOP_LEFT, Element::TEXT, 0, 18, 20, getHeight() - 40, true));
    addRessource(Ressource("Selectionner l'aeroport", Display::TOP_LEFT, Element::TEXT, 0, 18, 20, getHeight() - 76, true));

    int count(0);
    for (auto& el : getAerialNetwork().get_fleet()) {
        addRessource(Ressource(el.get_name(), Display::TOP_LEFT, Element::SELECTOR_AIRPLANE, 0, 18, 20, getHeight() - (count + 2)*30 - 16, true));
        count++;
    }

    count = 0;
    for (auto& el : getAerialNetwork().get_airports()) {
        addRessource(Ressource(el.get_name(), Display::TOP_LEFT, Element::SELECTOR_AIRPORT, 0, 18, 20, getHeight() - (count + 2)*30 - 52, true));
        count++;
    }

    if (TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
        return;
    }
    
    TTF_Font* font = TTF_OpenFont("rsc/fonts/SFPro_Regular.ttf", 18);
    if (font == nullptr) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "#1 [DEBUG] > %s", TTF_GetError());

    /*std::vector<SDL_Surface*> txts;
    for (auto& el : getAerialNetwork().get_fleet()) {
        txts.push_back(TTF_RenderText_Blended(font, el.get_name().c_str(), SDL_Color{255, 255, 255, 255}));
        cout << el.get_name() << "\n";
    }*/

    updateTextures();

    bool _airplane_selector_open = false;
    bool _airport_selector_open = false;

    SDL_Event events;
    bool isOpen{true};
    while (isOpen) {
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT:
                    isOpen = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (events.button.button == SDL_BUTTON_LEFT && isRessourceClicked(events.motion.x, events.motion.y)) {
                        Ressource* tmp = getRessourceClicked(events.motion.x, events.motion.y);

                        bool _need_panel_update = false;
                        // Toggle airplane panel
                        if (tmp->getPath() == "Selectionner un avion") {
                            _airplane_selector_open = !_airplane_selector_open;
                            if (_airplane_selector_open)_airport_selector_open = false;
                            _need_panel_update = true;
                        }   

                        // Toggle airport panel
                        if (tmp->getPath() == "Selectionner l'aeroport") {
                            _airport_selector_open = !_airport_selector_open;
                            _need_panel_update = true;
                        }

                        // Panel update
                        if (_need_panel_update) {
                            for (auto& el : getRessources()) {
                                if (el.getElement() == Element::SELECTOR_AIRPLANE) {
                                    el.setClickable(_airplane_selector_open);
                                    el.setRenderable(_airplane_selector_open);
                                } else if (el.getElement() == Element::SELECTOR_AIRPORT) {
                                    el.setClickable(_airport_selector_open);
                                    el.setRenderable(_airport_selector_open);
                                } else if (el.getPath() == "Selectionner l'aeroport") {
                                    el.setClickable(!_airplane_selector_open);
                                    el.setRenderable(!_airplane_selector_open);
                                } 
                            }
                            updateTextures();
                        }


                        // Select current airplane
                        if (tmp->getElement() == Element::SELECTOR_AIRPLANE) {
                            SDL_Log("Selector triggered\n");
                            // Updating current airplane
                            for (auto& el : getAerialNetwork().get_fleet()) {
                                if (el.get_name() == tmp->getPath()) {
                                    set_current_airplane(el);
                                    break;
                                }
                            }
                            // Updating color text
                            for (auto& el : getRessources()) {
                                if (el.getElement() == Element::SELECTOR_AIRPLANE ) {
                                        if (TTF_Init() < 0) {
                                            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
                                            return;
                                        }
                                        if (el.getPath() == get_current_airplane().get_name())
                                            el.setSurface(TTF_RenderText_Blended(font, el.getPath().c_str(), SDL_Color{0, 255, 255, 255}));
                                        else 
                                            el.setSurface(TTF_RenderText_Blended(font, el.getPath().c_str(), SDL_Color{255, 255, 255, 255}));
                                    }
                            }
                            updateTextures();
                        }

                        // Select current airport
                        if (tmp->getElement() == Element::SELECTOR_AIRPORT) {
                            SDL_Log("Selector airport triggered\n");
                            // Updating current aiport
                            for (auto& el : getAerialNetwork().get_airports()) {
                                if (el.get_name() == tmp->getPath()) {
                                    set_current_airport(el);
                                    break;
                                }
                            }
                            // Updating color text
                            for (auto& el : getRessources()) {
                                if (el.getElement() == Element::SELECTOR_AIRPORT ) {
                                        if (TTF_Init() < 0) {
                                            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
                                            return;
                                        }
                                        if (el.getPath() == get_current_airport().get_name())
                                            el.setSurface(TTF_RenderText_Blended(font, el.getPath().c_str(), SDL_Color{0, 255, 255, 255}));
                                        else 
                                            el.setSurface(TTF_RenderText_Blended(font, el.getPath().c_str(), SDL_Color{255, 255, 255, 255}));
                                    }
                            }
                            updateTextures();
                        }

                    }
                    break;

                default: break;
            }
        }
        
        SDL_SetRenderDrawColor(getRender(), 0, 0, 0, 255); 
        SDL_RenderClear(getRender());

        // Appending differents ressources
        SDL_SetRenderDrawColor(getRender(), 0, 255, 0, 255);

        for (auto& el : getTextures())
            SDL_RenderCopy(getRender(), el.first, NULL, &el.second);

        SDL_RenderPresent(getRender());  
 
    }
    close();
}

Ressource* GameWindow::getRessourceClicked(int _x, int _y) {
    for (auto& el : getRessources())
        if (el.isClickable())
            if (_x >= el.getRelativeX() && _x < el.getRelativeX() + el.getWidth() && _y >= el.getRelativeY() && _y < el.getRelativeY() + el.getHeight())
                return &el;
    return NULL;
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