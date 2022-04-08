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
    //setWindow(NULL);
    //SDL_Quit();
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
    //addRessource(Ressource("rsc/cursor.png",Display::CENTER, 37, 30, 300, 400, false));

    addRessource(Ressource("Simulation",Display::CENTER, Element::TEXT, 0, 18, getWidth()/2, (getHeight()/2)-25, true));
    addRessource(Ressource("Configuration", Display::CENTER ,Element::TEXT, 0, 18, getWidth()/2, (getHeight()/2)+15, true));
    addRessource(Ressource("Credits", Display::CENTER, Element::TEXT, 0, 18, getWidth()/2 , (getHeight()/2)+55, true));
    addRessource(Ressource("Quitter", Display::CENTER , Element::TEXT, 0, 18, getWidth()/2 , (getHeight()/2)+95, true));


    if (TTF_Init() < 0) return;
 
    TTF_Font* font = TTF_OpenFont("rsc/fonts/SFPro_Semibold.ttf", 24);
    if (font == nullptr) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "#1 [DEBUG] > %s", TTF_GetError());
    for(auto& el:getRessources())
        if(el.getElement() == Element::TEXT)
            el.setSurface(TTF_RenderText_Blended(font, el.getPath().c_str(), SDL_Color{255, 255, 255}));
    
    updateTextures();
    Ressource* last_ressource = NULL;

    // Events managing
    SDL_Event events;


    bool open{true};
    State current_state = State::RUNNING;
    while (current_state == State::RUNNING) {
        while (SDL_PollEvent(&events)) {
            Ressource* temp;   
            switch (events.type) {
                case SDL_QUIT:       
                    current_state == State::LEAVING;
                    break;
                case SDL_MOUSEMOTION:
                    temp = getRessourceClicked(events.motion.x, events.motion.y);
                    if (temp != last_ressource) {
                        for (auto& el : getRessources()) 
                            if (el.getElement() == Element::TEXT)
                                el.setSurface(TTF_RenderText_Blended(font, el.getPath().c_str(), SDL_Color{(temp == NULL ? 255 : (el.getPath() == temp->getPath() ? 0 : 255)), 255, 255}));
                        updateTextures();
                        last_ressource = temp;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (events.button.button == SDL_BUTTON_LEFT && isRessourceClicked(events.motion.x, events.motion.y))
                        current_state = handle_click_on_menu(getRessourceClicked(events.motion.x, events.motion.y));
                    break;    
                default: break;
            }
        }
        render(false);
    }
    close();
    if (current_state == State::SIMULATE)
        run();
    if (current_state == State::LEAVING) {
        setWindow(NULL);
        SDL_Quit();
    }
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

void GameWindow::run() {
    if (!init()) printf("Failed to initialize!\n");
    else SDL_UpdateWindowSurface(getWindow());
    
    getRessources().clear();

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

bool GameWindow::isRessourceClicked(int _x, int _y) {
    for (auto& el : getRessources())
        if (el.isClickable())
            if (_x >= el.getRelativeX() && _x < el.getRelativeX() + el.getWidth() && _y >= el.getRelativeY() && _y < el.getRelativeY() + el.getHeight())
                return true;
    return false;
}

vector<Edge> GameWindow::drawGraph(Graph graph) {
    
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

State GameWindow::handle_click_on_menu(Ressource* _clicked_ressource) {
    string _str = _clicked_ressource->getPath();
    if (_str == "Quitter")
        return State::LEAVING;
    else if (_str == "Simulation") {
        return State::SIMULATE;
    }
    
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