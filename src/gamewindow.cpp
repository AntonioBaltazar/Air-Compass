#include <math.h>
#include "gamewindow.h"
#include "graphicelement.h"
#include "utils.h"
#define M_PI           3.14159265358979323846

using namespace std;
using namespace Utils;

void GameWindow::updateTextures() {
    m_textures.clear();
    for (auto& el : m_ressources)
        if (!el.get_event_config()._renderable) continue;
        else if (el.getElement() == Element::IMAGE)
            m_textures.push_back(make_pair(SDL_CreateTextureFromSurface(m_renderer, el.getSurface()), 
                SDL_Rect{el.getRelativeX(), el.getRelativeY(), el.getWidth(), el.getHeight()}));
        else if (el.getElement() == Element::TEXT || el.getElement() == Element::SELECTOR_AIRPLANE || el.getElement() == Element::SELECTOR_AIRPORT)
            m_textures.push_back(make_pair(SDL_CreateTextureFromSurface(m_renderer, el.getSurface()), 
                SDL_Rect{el.getRelativeX(), el.getRelativeY(), el.getWidth(), el.getHeight()}));
    m_need_render =  true;
}

void GameWindow::updateTexture(std::string _path) {
    Ressource* tmp = NULL;
    int i = 0;
    for (auto& el : m_ressources) 
        if (el.getPath() == _path) {
            tmp = &el;
            i++;
        }
    if (tmp == NULL) return;
    m_textures[i] = make_pair(SDL_CreateTextureFromSurface(m_renderer, tmp->getSurface()), 
            SDL_Rect{tmp->getRelativeX(), tmp->getRelativeY(), tmp->getWidth(), tmp->getHeight()});
}

void GameWindow::launch()
{
    // Adding differents ressources
    addRessource(Ressource("rsc/menu2.jpg", Display::TOP_LEFT, m_screen_width, m_screen_height, 0, 0, {false, true}));
    // Texts
    addRessource(Ressource(Element::TEXT, "Simulation", "SFPro_Semibold", 24, Display::CENTER, 
        m_screen_width/2, (m_screen_height/2)-25, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));
    addRessource(Ressource(Element::TEXT, "Configuration", "SFPro_Semibold", 24, Display::CENTER, 
        m_screen_width/2, (m_screen_height/2)+15, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));
    addRessource(Ressource(Element::TEXT, "Credits", "SFPro_Semibold", 24, Display::CENTER, 
        m_screen_width/2, (m_screen_height/2)+55, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));
    addRessource(Ressource(Element::TEXT, "Quitter", "SFPro_Semibold", 24, Display::CENTER, 
        m_screen_width/2, (m_screen_height/2)+95, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));

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
                    SDL_Log("x: %d, y: %d\n", events.motion.x, events.motion.y);
                    temp = getRessourceClicked(events.motion.x, events.motion.y);
                    if (temp != last_ressource) {
                        if (temp != NULL && temp->getElement() == Element::TEXT)
                            play_sound("hovering.mp3", 30, false);
                        for (auto& el : m_ressources) 
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
    m_ressources.clear();
    addRessource(Ressource("rsc/realmap.jpg", Display::TOP_LEFT, m_screen_width, m_screen_height, 0, 0, {false, true}));

    // Add resssources from graph
    get_graph().load_from_file("graph.txt");
    get_edges() = drawGraph(get_graph());

    // Text
    addRessource(Ressource(Element::TEXT, "Selectionner un avion", "SFPro_Regular", 18, Display::TOP_LEFT, 
        20, m_screen_height - 40, {255, 255, 255}, {0, 255, 255}, {0, 255, 255}));
    addRessource(Ressource(Element::TEXT, "Selectionner l'aeroport", "SFPro_Regular", 18, Display::TOP_LEFT, 
        20, m_screen_height - 76, {255, 255, 255}, {0, 255, 255}, {0, 255, 255}));
    addRessource(Ressource(Element::TEXT, "Simulation aleatoire", "SFPro_Regular", 18, Display::TOP_LEFT, 
        m_screen_width - 200, m_screen_height - 40, {255, 255, 255}, {0, 255, 255}, {0, 255, 255}));

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
    for (auto& el : m_ressources)
        if (el.get_event_config()._clickable)
            if (_x >= el.getRelativeX() && _x < el.getRelativeX() + el.getWidth() && _y >= el.getRelativeY() && _y < el.getRelativeY() + el.getHeight())
                return &el;
    return NULL;
}

bool GameWindow::isRessourceClicked(int _x, int _y) {
    for (auto& el : m_ressources)
        if (el.get_event_config()._clickable)
            if (_x >= el.getRelativeX() && _x < el.getRelativeX() + el.getWidth() && _y >= el.getRelativeY() && _y < el.getRelativeY() + el.getHeight())
                return true;
    return false;
}

vector<Edge> GameWindow::drawGraph(Graph graph) {
    
    // Affichage des aéroports
    for (auto& el : graph.get_airports())
        addRessource(Ressource("rsc/airport.gif", Display::CENTER, 64, 48, el->get_x(), el->get_y()));
    
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
    else if (_str == "Simulation")
        return State::SIMULATE;
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

    if (_clicked_ressource->get_text_params()._text == "Simulation aleatoire") {
        SDL_Log("Simulation | / -");
        m_simulation = Simulation(&m_aerialnetwork, &m_graph);
        m_simulation.generate(10);
        _need_panel_update = true;
    }

    // Panel update
    if (_need_panel_update) {
        for (auto& el : m_ressources)
            if (el.getElement() == Element::SELECTOR_AIRPLANE)
                el.get_event_config() = {_params->_airplane_selector_open, _params->_airplane_selector_open};
            else if (el.getElement() == Element::SELECTOR_AIRPORT)
                el.get_event_config() = {_params->_airport_selector_open, _params->_airport_selector_open};
            else if (el.get_text_params()._text == "Selectionner l'aeroport")
                el.get_event_config() = {!_params->_airplane_selector_open, !_params->_airplane_selector_open};
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
        for (auto& el : m_ressources) 
            if (el.getElement() == Element::SELECTOR_AIRPLANE || el.getElement() == Element::SELECTOR_AIRPORT) {
                    if (TTF_Init() < 0) return;
                    TTF_Init();
                    TTF_Font* font = TTF_OpenFont(("rsc/fonts/" + std::string(el.get_text_params()._font) + ".ttf").c_str(), el.get_text_params()._font_size);
                    if (font != NULL)
                        el.setSurface(TTF_RenderText_Blended(font, el.get_text_params()._text.c_str(), (el.get_text_params()._text == m_current_airplane.get_name() 
                        || el.get_text_params()._text == m_current_airport.get_name() ) ? el.get_text_params()._active_color : el.get_text_params()._default_color));
                    TTF_CloseFont(font);
            }
        updateTextures();
    }
}

void GameWindow::render_simulation() {
    // Pour chaque trajet on affiche une lettre sur la ligne en fonction du nombre de tick puis incrémentation
    for (auto& flight : m_simulation.get_flights()) {
       // Coord src_c = flight.get_dest();
       Airport* src = get_airport(flight.get_edge().src);
       Airport* dest = get_airport(flight.get_edge().dest);

       Coord src_c = {src->get_x(), src->get_y()};
       Coord dest_c = {dest->get_x(), dest->get_y()};

       
    }
}

void GameWindow::render_edges() {
    m_graph_params._need_edges_update = false;
    

    SDL_SetRenderDrawColor(m_renderer, 229, 36, 36, 255);
    for (auto& edge : m_edges) {
        
        string text; 
        text.append(to_string(edge.weigth*200));
        text.append("km");
        
        TTF_Init();
        int font_size = edge.weigth < 20 ? 10 : 16;
        TTF_Font* _font = TTF_OpenFont("rsc/fonts/SFPro_Semibold.ttf", font_size);
        if (_font == nullptr) return;
        SDL_Surface* text_surface = TTF_RenderText_Blended(_font, text.c_str(), SDL_Color{229, 36, 36, 255});
        TTF_CloseFont(_font);

        int x1 = m_graph.get_airports()[edge.src]->get_x();
        int y1 = m_graph.get_airports()[edge.src]->get_y();
        int x2 = m_graph.get_airports()[edge.dest]->get_x();
        int y2 = m_graph.get_airports()[edge.dest]->get_y();

        int mid_x = (x1 + x2 - text_surface->w-2) / 2;
        int mid_y = (y1 + y2 - text_surface->w-2) / 2;

        double angle_radian = atan2(y1 - y2, x1 - x2);    
        double angle = angle_radian * 180.0 / M_PI;
        angle = (angle < -90) ? angle + 180 : (angle > 90 ? angle - 180 : angle);


        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);
        SDL_FRect rect{mid_x + (float)font_size*abs(sin(angle_radian)), mid_y + (float)font_size*abs(cos(angle_radian)), text_surface->w, text_surface->h};

        SDL_RenderCopyExF(m_renderer, texture, NULL, &rect, angle, NULL, SDL_RendererFlip());
        SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);

        SDL_DestroyTexture( texture );
        SDL_FreeSurface( text_surface );
    }
    
}

void GameWindow::render() {
    if (m_need_render) {
        SDL_RenderClear(m_renderer);

        // Render background
        SDL_RenderCopy(m_renderer, m_textures[0].first, NULL, &(m_textures[0].second));
        SDL_DestroyTexture(m_textures[0].first);

        render_edges();
        if (m_simulation.is_running())
            render_simulation();

        // Render others things
        for (auto i = m_textures.begin() + 1; i != m_textures.end(); i++) {
            SDL_RenderCopy(m_renderer, (*i).first, NULL, &(*i).second);
            SDL_DestroyTexture((*i).first);
        }

        SDL_RenderPresent(m_renderer);  
        m_need_render = false;
    }
}

void GameWindow::play_sound(string _music_name, int _volume, bool _loop) {
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
        return;
    }

    Mix_Music* music = Mix_LoadMUS(("rsc/sounds/" + std::string(_music_name)).c_str()); // Charge notre musique

    if (music == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }
    Mix_VolumeMusic(_volume);
    Mix_PlayMusic(music, (_loop ? -1 : 0)); // Joue notre musique 
}
