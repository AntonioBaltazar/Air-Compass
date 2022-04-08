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

void GameWindow::updateTextures() {
    getTextures().clear();
    for (auto& el : getRessources())
        if (!el.get_event_config()._renderable) continue;
        else if (el.getElement() == Element::IMAGE)
            getTextures().push_back(make_pair(SDL_CreateTextureFromSurface(getRender(), el.getSurface()), 
                SDL_Rect{el.getRelativeX(), el.getRelativeY(), el.getWidth(), el.getHeight()}));
        else if (el.getElement() == Element::TEXT || el.getElement() == Element::SELECTOR_AIRPLANE || el.getElement() == Element::SELECTOR_AIRPORT)
            getTextures().push_back(make_pair(SDL_CreateTextureFromSurface(getRender(), el.getSurface()), 
                SDL_Rect{el.getRelativeX(), el.getRelativeY(), el.getWidth(), el.getHeight()}));
    m_need_render =  true;
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

void GameWindow::launch()
{
    // Adding differents ressources
    addRessource(Ressource("rsc/menu.jpg", Display::TOP_LEFT, 1333, 900, 0, 0, {false, true}));
    // Texts
    addRessource(Ressource(Element::TEXT, "Simulation", "SFPro_Semibold", 24, Display::CENTER, 
        getWidth()/2, (getHeight()/2)-25, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));
    addRessource(Ressource(Element::TEXT, "Configuration", "SFPro_Semibold", 24, Display::CENTER, 
        getWidth()/2, (getHeight()/2)+15, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));
    addRessource(Ressource(Element::TEXT, "Credits", "SFPro_Semibold", 24, Display::CENTER, 
        getWidth()/2, (getHeight()/2)+55, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));
    addRessource(Ressource(Element::TEXT, "Quitter", "SFPro_Semibold", 24, Display::CENTER, 
        getWidth()/2, (getHeight()/2)+95, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));

    updateTextures();
    Ressource* last_ressource = NULL;

    // Events managing
    SDL_Event events;

    State current_state = State::RUNNING;
    while (current_state == State::RUNNING) {
        while (SDL_PollEvent(&events)) {
            Ressource* temp;   
            switch (events.type) {
                case SDL_QUIT:       
                    current_state = State::LEAVING;
                    break;
                case SDL_MOUSEMOTION:
                    temp = getRessourceClicked(events.motion.x, events.motion.y);
                    if (temp != last_ressource) {
                        for (auto& el : getRessources()) 
                            if (el.getElement() == Element::TEXT) {
                                TTF_Init();
                                TTF_Font* font = TTF_OpenFont(("rsc/fonts/" + string(el.get_text_params()._font) + ".ttf").c_str(), el.get_text_params()._font_size);
                                if (font == NULL) continue;
                                el.setSurface(TTF_RenderText_Blended(font, el.get_text_params()._text.c_str(), temp == NULL ? el.get_text_params()._default_color : 
                                    (el.get_text_params()._text == temp->get_text_params()._text ? el.get_text_params()._hover_color : el.get_text_params()._default_color)));
                                TTF_CloseFont(font);
                            }
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
        render();
    }

    if (current_state == State::SIMULATE)
        run();
}

void GameWindow::run() {
    getRessources().clear();
    addRessource(Ressource("rsc/realmap.jpg", Display::TOP_LEFT, 1333, 900, 0, 0, {false, true}));

    // Add resssources from graph
    get_graph().load_from_file("graph.txt");
    get_edges() = drawGraph(get_graph());

    // Text
    addRessource(Ressource(Element::TEXT, "Selectionner un avion", "SFPro_Regular", 18, Display::TOP_LEFT, 
        20, m_screen_height - 40, {255, 255, 255}, {0, 255, 255}, {0, 255, 255}));
    addRessource(Ressource(Element::TEXT, "Selectionner l'aeroport", "SFPro_Regular", 18, Display::TOP_LEFT, 
        20, m_screen_height - 76, {255, 255, 255}, {0, 255, 255}, {0, 255, 255}));

    int count(0);
    for (auto& el : getAerialNetwork().get_fleet()) {
        addRessource(Ressource(Element::SELECTOR_AIRPLANE, el.get_name(), "SFPro_Regular", 18, Display::TOP_LEFT, 
            20, m_screen_height - (count + 2)*30 - 16, {255, 255, 255}, {0, 255, 255}, {0, 255, 255}));
        count++;
    }

    count = 0;
    for (auto& el : getAerialNetwork().get_airports()) {
        addRessource(Ressource(Element::SELECTOR_AIRPORT, el.get_name(), "SFPro_Regular", 18, Display::TOP_LEFT, 
            20, m_screen_height - (count + 2)*30 - 52, {255, 255, 255}, {0, 255, 255}, {0, 255, 255}));
        count++;
    }

    PanelParams _params;
    updateTextures();

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
                    }
                    break;
                default: break;
            }
        }
        render();
    }
}

Ressource* GameWindow::getRessourceClicked(int _x, int _y) {
    for (auto& el : getRessources())
        if (el.get_event_config()._clickable)
            if (_x >= el.getRelativeX() && _x < el.getRelativeX() + el.getWidth() && _y >= el.getRelativeY() && _y < el.getRelativeY() + el.getHeight())
                return &el;
    return NULL;
}

bool GameWindow::isRessourceClicked(int _x, int _y) {
    for (auto& el : getRessources())
        if (el.get_event_config()._clickable)
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
    string _str = _clicked_ressource->get_text_params()._text;
    if ( _str == "Quitter")
        return State::LEAVING;
    else if (_str == "Simulation") {
        return State::SIMULATE;
    }
    return State::RUNNING;
}

void GameWindow::updateGraph() {
    Graph g = get_graph();
    g.limitEdge(m_current_airplane.get_autonomy() / 200);

    get_edges() = drawGraph(g);
    get_graph_params()._need_edges_update = true;
}

void GameWindow::handlePanels(Ressource* _clicked_ressource, PanelParams* _params) {
    
    bool _need_panel_update;

    // Toggle airplane panel
    if (_clicked_ressource->get_text_params()._text == "Selectionner un avion") {
        _params->_airplane_selector_open = !_params->_airplane_selector_open;
        if (_params->_airplane_selector_open) _params->_airport_selector_open = false;
        _need_panel_update = true;
    }   

    // Toggle airport panel
    if (_clicked_ressource->get_text_params()._text == "Selectionner l'aeroport") {
        _params->_airport_selector_open = !_params->_airport_selector_open;
        _need_panel_update = true;
    }

    // Panel update
    if (_need_panel_update) {
        for (auto& el : getRessources()) {
            if (el.getElement() == Element::SELECTOR_AIRPLANE) {
                el.get_event_config() = {_params->_airplane_selector_open, _params->_airplane_selector_open};
            } else if (el.getElement() == Element::SELECTOR_AIRPORT) {
                el.get_event_config() = {_params->_airport_selector_open, _params->_airport_selector_open};
            } else if (el.get_text_params()._text == "Selectionner l'aeroport") {
                el.get_event_config() = {!_params->_airplane_selector_open, !_params->_airplane_selector_open};
            } 
        }
        updateTextures();
    }

    bool _need_text_update = false;
    // Select current airplane
    if (_clicked_ressource->getElement() == Element::SELECTOR_AIRPLANE) {
        for (auto& el : getAerialNetwork().get_fleet()) {
            if (el.get_name() == _clicked_ressource->get_text_params()._text) {
                set_current_airplane(el);
                updateGraph();
                break;
            }
        }
        _need_text_update = true;
    }

    // Select current airport
    if (_clicked_ressource->getElement() == Element::SELECTOR_AIRPORT) {
        for (auto& el : getAerialNetwork().get_airports()) {
            if (el.get_name() == _clicked_ressource->get_text_params()._text) {
                set_current_airport(el);
                break;
            }
        }
        _need_text_update = true;
    }

    // Updating text color
    if (_need_text_update) {
        for (auto& el : getRessources()) 
            if (el.getElement() == Element::SELECTOR_AIRPLANE || el.getElement() == Element::SELECTOR_AIRPORT) {
                    if (TTF_Init() < 0) return;
                    TTF_Init();
                    TTF_Font* font = TTF_OpenFont(("rsc/fonts/" + std::string(el.get_text_params()._font) + ".ttf").c_str(), el.get_text_params()._font_size);
                    if (font != NULL)
                        el.setSurface(TTF_RenderText_Blended(font, el.get_text_params()._text.c_str(), (el.get_text_params()._text == get_current_airplane().get_name() 
                        || el.get_text_params()._text == get_current_airport().get_name() ) ? el.get_text_params()._active_color : el.get_text_params()._default_color));
                    TTF_CloseFont(font);
            }
        updateTextures();
    }
}

void GameWindow::render_edges() {
    if (TTF_Init() < 0) return;
    m_graph_params._need_edges_update = false;
    TTF_Font* _font = TTF_OpenFont("rsc/fonts/SFPro_Regular.ttf", 18);
    if (_font == nullptr) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "#1 [DEBUG] > %s", TTF_GetError());

    SDL_SetRenderDrawColor(getRender(), 253, 70, 38, 255);
    for (auto& edge : m_edges) {

        int x1 = m_graph.get_airports()[edge.src]->get_x();
        int y1 = m_graph.get_airports()[edge.src]->get_y();
        int x2 = m_graph.get_airports()[edge.dest]->get_x();
        int y2 = m_graph.get_airports()[edge.dest]->get_y();

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

void GameWindow::render() {
    if (m_need_render) {
        SDL_Log("Rendering\n");
        SDL_RenderClear(getRender());

        // Render background
        SDL_RenderCopy(getRender(), getTextures()[0].first, NULL, &(getTextures()[0].second));

        render_edges();

        // Render others things
        for (auto i = getTextures().begin() + 1; i != getTextures().end(); i++)
            SDL_RenderCopy(getRender(), (*i).first, NULL, &(*i).second);

        SDL_RenderPresent(getRender());  
        m_need_render = false;
    }
}