#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <math.h>
#include "gamewindow.h"
#include "graphicelement.h"
#define M_PI           3.14159265358979323846

using namespace std;

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
    //addRessource(Ressource("rsc/cursor.png",Display::CENTER, 37, 30, 300, 400, false));

    addRessource(Ressource("Lancer la simulation",Display::CENTER, Element::TEXT, 0, 18, getWidth()/2 , (getHeight()/2)-30, true));
    addRessource(Ressource("Panneau de controle", Display::CENTER ,Element::TEXT, 0, 18, getWidth()/2 , (getHeight()/2)+20, true));
    addRessource(Ressource("Credit", Display::CENTER, Element::TEXT, 0, 18, getWidth()/2 , (getHeight()/2)+70, true));
    addRessource(Ressource("Quitter", Display::CENTER , Element::TEXT, 0, 18, getWidth()/2 , (getHeight()/2)+120, true));


    if (TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
        return;
    }

    TTF_Font* font = TTF_OpenFont("rsc/fonts/SFPro_Regular.ttf", 30);
    if (font == nullptr) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "#1 [DEBUG] > %s", TTF_GetError());
    for(auto& el:getRessources())
        if(el.getElement() == Element::TEXT)
            el.setSurface(TTF_RenderText_Blended(font, el.getPath().c_str(), SDL_Color{255, 255, 255}));
    
    
    updateTextures();
    
    // Events managing
    SDL_Event events;
    bool open{true};
    while (open) {
        // SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
        while (SDL_PollEvent(&events)) {
            Ressource* temp;
            if(choice > 4) choice = 0;
            if(choice < 0) choice = 4;     

            switch (events.type) {
                
                case SDL_QUIT:        // If window's closed we quit sdl mode 
                    open = false;
                    break;

                case SDL_MOUSEMOTION:
                    // Updating text color
                    // for( auto& el:getRessources())
                    //     if(el.getElement() == Element::TEXT && mouse_coordinates(events,el.getX(),el.getWidth(),el.getY(),el.getHeight())){
                    //         el.setSurface(TTF_RenderText_Blended(font, el.getPath().c_str(), SDL_Color{0, 255, 255}));
                    //         updateTextures();
                    //         SDL_Log("OK");
                    //     }
                    // SDL_Log("OK1");
                    SDL_Log("Mouvement de souris (%d %d) (%d %d)", events.motion.x, events.motion.y, events.motion.xrel, events.motion.yrel);
                        temp = getRessourceClicked(events.motion.x,events.motion.y);
                        if(temp == NULL) break;
                        if(temp->getElement() == Element::TEXT){
                            temp->setSurface(TTF_RenderText_Blended(font, temp->getPath().c_str(), SDL_Color{0, 255, 255}));
                            updateTextures();
                         if(temp->getPath() == "notpointed")
                            temp->setSurface(TTF_RenderText_Blended(font, temp->getPath().c_str(), SDL_Color{255, 255, 255}));
                        }
                break;    

                // case SDL_KEYDOWN:     // Key has been pressed  
                //     // If it's escape key then we also quit sdl mode
                //     if(events.key.keysym.scancode == SDL_SCANCODE_ESCAPE) open = SDL_FALSE;
                    
                //     if(events.key.keysym.scancode == SDL_SCANCODE_UP && choice > 0) {
                //         choice--;
                //         // cursor_move(choice);
                //         SDL_Delay(20);
                //     }
                    
                //     else if(events.key.keysym.scancode == SDL_SCANCODE_DOWN && choice < 4){
                //         choice++;
                //         // cursor_move(choice);
                //         SDL_Delay(100);
                //     } 
                    
                //     break;

                default: break;

            }
                // SDL_Log("Choice = %d",choice);
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
    if(choice == 0)
        m_ressources[1].setY(400);
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

    // Add resssources from graph
    //Graph graph("graph.txt");
    get_graph().load_from_file("graph.txt");
    get_edges() = drawGraph(get_graph());

    // Text
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

    PanelParams _params;
    updateTextures();

    bool update_edges = false;

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
                        handlePanels(tmp, &_params);
                        update_edges = !update_edges;
                    }
                    break;
                default: break;
            }
        }
        render(update_edges);
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

Ressource* GameWindow::getRessourceClicked2(int _x, int _y) {
    for (auto& el : getRessources())
        if (el.isClickable()){
            if (_x >= el.getRelativeX() && _x < el.getRelativeX() + el.getWidth() && _y >= el.getRelativeY() && _y < el.getRelativeY() + el.getHeight())
                return &el;
        }
        else{
            Ressource* temp;
            temp->setPath("notpointed");
            return temp;
        }
    return NULL;
}


bool GameWindow::isRessourceClicked(int _x, int _y) {
    for (auto& el : getRessources())
        if (el.isClickable())
            if (_x >= el.getRelativeX() && _x < el.getRelativeX() + el.getWidth() && _y >= el.getRelativeY() && _y < el.getRelativeY() + el.getHeight())
                return true;
    return false;
}

vector<Edge> GameWindow::drawGraph(Graph graph) {
    

    // Pour chaque sommet affichage 
    // Puis pour chaque adjacent tracage
    // Lier l'airport grâce au nom

    // Affichage des aéroports
    for (auto& el : graph.get_airports())
        addRessource(Ressource("rsc/airport.gif", Display::CENTER, 63, 48, el->get_x(), el->get_y()));
    
    // Affichage des arrêtes
    
    vector<Edge> edges;
    // Getting edges
    for (int i = 0; i < graph.get_nb_vertices(); i++) {
        for (auto& el : graph.get_adj()[i]) {
            bool exist = false;
            for (auto& edge : edges)
                if (edge.dest == i && edge.src == el.first.get_num()) {
                    exist = true;
                    break;
                }
            if (!exist) edges.push_back({i, el.first.get_num(), el.second});
        }
    }
    // Affichage arrête
    for (auto& edge : edges) {
        cout << edge.src << " " << edge.dest << " " << edge.weigth << "\n";
    }
    return edges;
}

void GameWindow::handlePanels(Ressource* _clicked_ressource, PanelParams* _params) {
    
    if (TTF_Init() < 0) return;

    TTF_Font* _font = TTF_OpenFont("rsc/fonts/SFPro_Regular.ttf", 18);
    if (_font == nullptr) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "#1 [DEBUG] > %s", TTF_GetError());

    bool _need_panel_update;

    // Toggle airplane panel
    if (_clicked_ressource->getPath() == "Selectionner un avion") {
        _params->_airplane_selector_open = !_params->_airplane_selector_open;
        if (_params->_airplane_selector_open) _params->_airport_selector_open = false;
        _need_panel_update = true;
    }   

    // Toggle airport panel
    if (_clicked_ressource->getPath() == "Selectionner l'aeroport") {
        _params->_airport_selector_open = !_params->_airport_selector_open;
        _need_panel_update = true;
    }

    // Panel update
    if (_need_panel_update) {
        for (auto& el : getRessources()) {
            if (el.getElement() == Element::SELECTOR_AIRPLANE) {
                el.setClickable(_params->_airplane_selector_open);
                el.setRenderable(_params->_airplane_selector_open);
            } else if (el.getElement() == Element::SELECTOR_AIRPORT) {
                el.setClickable(_params->_airport_selector_open);
                el.setRenderable(_params->_airport_selector_open);
            } else if (el.getPath() == "Selectionner l'aeroport") {
                el.setClickable(!_params->_airplane_selector_open);
                el.setRenderable(!_params->_airplane_selector_open);
            } 
        }
        updateTextures();
    }

    bool _need_text_update = false;
    // Select current airplane
    if (_clicked_ressource->getElement() == Element::SELECTOR_AIRPLANE) {
        for (auto& el : getAerialNetwork().get_fleet()) {
            if (el.get_name() == _clicked_ressource->getPath()) {
                set_current_airplane(el);
                break;
            }
        }
        _need_text_update = true;
    }

    // Select current airport
    if (_clicked_ressource->getElement() == Element::SELECTOR_AIRPORT) {
        for (auto& el : getAerialNetwork().get_airports()) {
            if (el.get_name() == _clicked_ressource->getPath()) {
                set_current_airport(el);
                break;
            }
        }
        _need_text_update = true;
    }

    // Updating text color
    if (_need_text_update) {
        for (auto& el : getRessources()) 
            if (el.getElement() == Element::SELECTOR_AIRPLANE ||
                el.getElement() == Element::SELECTOR_AIRPORT) 
                    el.setSurface(TTF_RenderText_Blended(_font, el.getPath().c_str(), SDL_Color{(el.getPath() == get_current_airplane().get_name() 
                        || el.getPath() == get_current_airport().get_name() ? 0 : 255), 255, 255, 255}));
        updateTextures();
    }
}


double constrainAngle(double x){
    x = fmod(x + 180,360);
    if (x < 0)
        x += 360;
    return x - 180;
}

void GameWindow::render_edges() {
    if (TTF_Init() < 0) return;

    TTF_Font* _font = TTF_OpenFont("rsc/fonts/SFPro_Regular.ttf", 18);
    if (_font == nullptr) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "#1 [DEBUG] > %s", TTF_GetError());

    SDL_SetRenderDrawColor(getRender(), 253, 70, 38, 255);
    for (auto& edge : m_edges) {

        int x1 = m_graph.get_airports()[edge.src]->get_x() + 31;
        int y1 = m_graph.get_airports()[edge.src]->get_y() + 24;
        int x2 = m_graph.get_airports()[edge.dest]->get_x() + 31;
        int y2 = m_graph.get_airports()[edge.dest]->get_y() + 24;

        int mid_x = (x1 + x2) / 2;
        int mid_y = (y1 + y2) / 2;

        double angle = atan2(y1 - y2, x1 - x2) * 180.0 / M_PI;
        angle = (angle < -90) ? angle + 180 : (angle > 90 ? angle - 180 : angle);

        string text; 
        text.append(to_string(edge.weigth*200));
        text.append("km");

        SDL_Surface* text_surface = TTF_RenderText_Blended(_font, text.c_str(), SDL_Color{253, 70, 38, 255});
        SDL_Texture*  texture = SDL_CreateTextureFromSurface(getRender(), text_surface);
        SDL_Rect rect{mid_x, mid_y, text_surface->w, text_surface->h};

        SDL_RenderCopyEx(getRender(), texture, NULL, &rect, angle , NULL, SDL_RendererFlip());

        SDL_RenderDrawLineF(getRender(), x1, y1, x2, y2);
    }

}

void GameWindow::render(bool update_edges) {
    SDL_RenderClear(getRender());

    // Render background
    SDL_RenderCopy(getRender(), getTextures()[0].first, NULL, &(getTextures()[0].second));

    if (update_edges)
        render_edges();

    // Render others things
    for (auto i = getTextures().begin() + 1; i != getTextures().end(); i++)
        SDL_RenderCopy(getRender(), (*i).first, NULL, &(*i).second);

    SDL_RenderPresent(getRender());  
}