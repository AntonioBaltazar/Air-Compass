#include <math.h>
#include <random>
#include <iomanip>
#include "gamewindow.h"
#include "audio.h"
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

void GameWindow::launch() {
    m_ressources.clear();
    // Adding differents ressources
    addRessource(Ressource("rsc/menu2.jpg", Display::TOP_LEFT, m_screen_width, m_screen_height, 0, 0, {false, true}));
    // Texts
    addRessource(Ressource(Element::TEXT, "Simulation", "SFPro_Semibold", 30, Display::CENTER, 
        m_screen_width/2, (m_screen_height/2)-35, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));
    addRessource(Ressource(Element::TEXT, "Configuration", "SFPro_Semibold", 30, Display::CENTER, 
        m_screen_width/2, (m_screen_height/2)+25, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));
    addRessource(Ressource(Element::TEXT, "Credits", "SFPro_Semibold", 30, Display::CENTER, 
        m_screen_width/2, (m_screen_height/2)+85, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));
    addRessource(Ressource(Element::TEXT, "Quitter", "SFPro_Semibold", 30, Display::CENTER, 
        m_screen_width/2, (m_screen_height/2)+145, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));

    m_need_render = true;
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
                    temp = getRessourceClicked(events.motion.x, events.motion.y, 0);
                    if (temp != last_ressource) {
                        if (temp != NULL && temp->getElement() == Element::TEXT)
                            playSound("rsc/sounds/hovering.wav", SDL_MIX_MAXVOLUME);
                        for (auto& el : m_ressources) 
                            if (el.getElement() == Element::TEXT) {
                                TTF_Init();
                                TTF_Font* font = TTF_OpenFont(("rsc/fonts/" + string(el.get_text_params()._font) + ".ttf").c_str(), el.get_text_params()._font_size);
                                if (font == NULL) continue;
                                el.setSurface(TTF_RenderText_Blended(font, el.get_text_params()._text.c_str(), temp == NULL ? el.get_text_params()._default_color : 
                                    (el.get_text_params()._text == temp->get_text_params()._text ? el.get_text_params()._hover_color : el.get_text_params()._default_color)));
                                TTF_CloseFont(font);
                            }
                        m_need_render = true;
                        last_ressource = temp;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (events.button.button == SDL_BUTTON_LEFT && isRessourceClicked(events.motion.x, events.motion.y))
                        current_state = handle_click_on_menu(getRessourceClicked(events.motion.x, events.motion.y, 0));
                    break;    
                default: break;
            }
        }
        render();
    }

    switch (current_state)
    {
        case State::SIMULATE:
            run();
            break;

        case State::CREDIT:
            if(display_credit(true) == 0)
                launch();
            break;
        case State::CONFIG:
            if(display_credit(false) == 0)
                launch();
            break;
        default: break;
    }

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
    addRessource(Ressource(Element::TEXT, "Retour", "SFPro_Semibold", 18, Display::CENTER, 
        m_screen_width/2, m_screen_height - 28, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));

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
    m_need_render = true;
    Ressource* last_ressource = NULL;

    SDL_Event events;
    bool isOpen{true};
    State current = State::RUNNING;
    while (current == State::RUNNING) {
        while (SDL_PollEvent(&events)) {
            Ressource* temp; 
            switch (events.type) {
                case SDL_QUIT:
                    current = State::LEAVING;
                    break;
                case SDL_MOUSEMOTION:
                    temp = getRessourceClicked(events.motion.x, events.motion.y, 10);
                    if (temp != last_ressource) {
                        if (temp != NULL && temp->getElement() == Element::TEXT)
                            playSound("rsc/sounds/hovering.wav", SDL_MIX_MAXVOLUME);
                        for (auto& el : m_ressources) 
                            if (el.getElement() == Element::TEXT || el.getElement() == Element::SELECTOR_AIRPLANE 
                                || el.getElement() == Element::SELECTOR_AIRPORT) {
                                TTF_Init();
                                TTF_Font* font = TTF_OpenFont(("rsc/fonts/" + string(el.get_text_params()._font) + ".ttf").c_str(), el.get_text_params()._font_size);
                                if (font == NULL) continue;
                                el.setSurface(TTF_RenderText_Blended(font, el.get_text_params()._text.c_str(), temp == NULL ? el.get_text_params()._default_color : 
                                    (el.get_text_params()._text == temp->get_text_params()._text ? el.get_text_params()._hover_color : el.get_text_params()._default_color)));
                                TTF_CloseFont(font);
                            }
                        m_need_render = true;
                        last_ressource = temp;
                    }
                case SDL_MOUSEBUTTONDOWN:
                    if (events.button.button == SDL_BUTTON_LEFT)
                        if(isRessourceClicked(events.motion.x, events.motion.y)) {
                        Ressource* tmp = getRessourceClicked(events.motion.x, events.motion.y, 0);
                            if (tmp != NULL)
                                if (tmp->get_text_params()._text == "Retour")
                                    current = State::CONFIG;
                            handlePanels(tmp, &_params);
                        } else {
                            if (m_airport_to_display != NULL) {
                                SDL_Log("debugging");
                                m_airport_to_display = NULL;
                                m_need_render = true;
                            }
                        }
                    break;
                default: break;
                
            }
        }
        if (m_simulation.is_running()) {
            m_simulation.next_step();
            SDL_Delay(1);
            //SDL_Log("Next step");
        }
        render();
    }
    m_simulation.set_running(false);
    m_edges.clear();

    switch (current) {
        case State::CONFIG:
            launch();
        break;
        default: break;
    }

}

Ressource* GameWindow::getRessourceClicked(int _x, int _y, int _padding) {
    for (auto& el : m_ressources)
        if (el.get_event_config()._clickable)
            if (_x >= el.getRelativeX() && _x < el.getRelativeX() + el.getWidth() && _y >= el.getRelativeY() - _padding && _y < el.getRelativeY() + el.getHeight() + _padding)
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
    if ( _str == "Quitter") return State::LEAVING;
    else if (_str == "Simulation")  return State::SIMULATE;
    else if (_str == "Configuration")   return State::CONFIG;
    else if (_str == "Credits") return State::CREDIT;

    return State::RUNNING;
}



int GameWindow::display_credit(bool credit)
{
      m_ressources.clear();
    if(credit)
        addRessource(Ressource("rsc/credits.jpg", Display::TOP_LEFT, m_screen_width, m_screen_height, 0, 0, {false, true}));
    else{
        addRessource(Ressource("rsc/configuration.jpg", Display::TOP_LEFT, m_screen_width, m_screen_height, 0, 0, {false, true}));
        addRessource(Ressource(Element::TEXT, "Cette fonctionnalitee arrivera dans une prochaine mise a jour", "SFPro_Regular", 25, Display::CENTER, 
            (m_screen_width)/2,500, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));   
        m_ressources.back().get_event_config()._clickable = false;
    }


    // Text
    addRessource(Ressource(Element::TEXT, "Retour", "SFPro_Semibold", 30, Display::CENTER, 
        m_screen_width/2,700, {206, 206, 206}, {255, 255, 255}, {255, 0, 255}));

    m_ressources[0].get_event_config()._clickable = false;
  
    m_need_render = true;
    Ressource* last_ressource = NULL;

    SDL_Event events;
    bool isOpen{true};
    while (isOpen) {
        while (SDL_PollEvent(&events)) {
            Ressource* temp = NULL;
            switch (events.type) {
                case SDL_QUIT:
                    isOpen = false;
                    return 1;
                    break;
                case SDL_MOUSEMOTION:
                    temp = getRessourceClicked(events.motion.x,events.motion.y, 0);
                    
                    if (temp != last_ressource) {
                        if (temp != NULL && temp->getElement() == Element::TEXT)
                            playSound("rsc/sounds/hovering.wav", SDL_MIX_MAXVOLUME);
                        for (auto& el : m_ressources) 
                            if (el.get_text_params()._text == "Retour") {
                                TTF_Init();
                                TTF_Font* font = TTF_OpenFont(("rsc/fonts/" + string(el.get_text_params()._font) + ".ttf").c_str(), el.get_text_params()._font_size);
                                if (font == NULL) continue;
                                el.setSurface(TTF_RenderText_Blended(font, el.get_text_params()._text.c_str(), temp == NULL ? el.get_text_params()._default_color : 
                                    (el.get_text_params()._text == temp->get_text_params()._text ? el.get_text_params()._hover_color : el.get_text_params()._default_color)));
                                TTF_CloseFont(font);
                            }
                        m_need_render = true;
                        last_ressource = temp;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (events.button.button == SDL_BUTTON_LEFT && isRessourceClicked(events.motion.x, events.motion.y)) {
                        isOpen = false;
                    }
                    break;
                default: break;
            }
        }
        render();
    }
    return 0;
}


void GameWindow::updateGraph() {
    Graph g = get_graph();
    g.limitEdge(m_current_airplane.get_autonomy() / 200);

    get_edges() = drawGraph(g);
    get_graph_params()._need_edges_update = true;
}

void GameWindow::handlePanels(Ressource* _clicked_ressource, PanelParams* _params) {
    
    bool _need_panel_update;

    if (_clicked_ressource->getElement() == Element::IMAGE &&
        _clicked_ressource->getPath() == "rsc/airport.gif") {
            m_airport_to_display = _clicked_ressource;
            _need_panel_update = true;
        }

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
        m_simulation.generate(30);
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
        m_need_render = true;
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
        m_need_render = true;
    }
}

void GameWindow::render_simulation() {
    for (auto& flight : m_simulation.get_flights()) {
        double pourcent = (double)flight.get_tick()/flight.get_edge().weigth;
        if (pourcent >= 1) continue;

        Airport* src = &m_aerialnetwork.get_airports()[flight.get_edge().src];
        Airport* dest = &m_aerialnetwork.get_airports()[flight.get_edge().dest];

        Coord src_c = {src->get_x(), src->get_y()};
        Coord dest_c = {dest->get_x(), dest->get_y()};

        double angle = atan2(dest_c.y - src_c.y, dest_c.x - src_c.x);
        double angle_n = angle * 180.0 / M_PI;
        double hyp = (double)pourcent*sqrt(pow(dest_c.y - src_c.y, 2) + pow(dest_c.x - src_c.x, 2));

        int x = hyp*cos(angle);
        int y = hyp*sin(angle);

        string str = "rsc/airplanes/" + to_string(flight.get_color()) +  ".svg";
        SDL_Texture* texture = IMG_LoadTexture(m_renderer, str);
        SDL_FRect rect{src_c.x+ x -15, src_c.y + y - 15, 30, 30};
 
        SDL_RenderCopyExF(m_renderer, texture, NULL, &rect, angle_n+147, NULL, SDL_RendererFlip());
        SDL_DestroyTexture( texture );
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
    if (m_need_render || m_simulation.is_running()) {
        updateTextures();
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

        if (m_airport_to_display != NULL) 
            render_airport();

        SDL_RenderPresent(m_renderer);  
        m_need_render = false;
        for (auto& txt : m_textures) {
            SDL_DestroyTexture(txt.first);
        }
    }
}

void GameWindow::render_airport() {

    string title_str;

    struct Text {
        string str;
        string font;
        int size;
    };

    vector<Text> texts;
    int x, y;
    for (auto& el : m_aerialnetwork.get_airports()) {
        if (el.get_x() == m_airport_to_display->getX() 
          && el.get_y() == m_airport_to_display->getY()) {
            title_str = el.get_name();
            texts.push_back({el.get_name(), "rsc/fonts/SFPro_Semibold.ttf", 14});
            setprecision(3);
            std::ostringstream longti, lati;
            longti << std::fixed;
            lati << std::fixed;
            longti << std::setprecision(4);
            lati << std::setprecision(4);
            longti << el.get_location().longtitude;
            lati << el.get_location().latitude;
            x = el.get_x() + 40;
            y = el.get_y() - 30;
            string loc = el.get_city() + " | GPS (" + longti.str() + ":" + lati.str() + ")";
            texts.push_back({loc, "rsc/fonts/SFPro_Regular.ttf", 14});
            break;
        }
    }
    
    int size_x = max(texts[0].str.size()*8, texts[1].str.size()*8) + 16;
    int size_y = 65;
    int count = 0;
    //SDL_Log("YES");
    if (size_x + x + 80 > m_screen_width) 
        x -= size_x + 80;

    SDL_Rect rectangle{x, y, size_x, size_y};

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_Texture* texture_rc = IMG_LoadTexture(m_renderer, "rsc/rect.svg");
    SDL_FRect rect_rc{x, y, size_x, size_y};
    SDL_RenderCopyExF(m_renderer, texture_rc, NULL, &rect_rc, 0, NULL, SDL_RendererFlip());
    SDL_DestroyTexture(texture_rc);


    for (auto& el : texts) {
        TTF_Init();
        TTF_Font* font = TTF_OpenFont(el.font.c_str(), el.size);
        if (font == nullptr) return;
        SDL_Surface* text_surface = TTF_RenderText_Blended(font, el.str.c_str(), SDL_Color{255, 255, 255, 255});
        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);
        SDL_FRect rect{x + 16, y + 12 + count*20, text_surface->w, text_surface->h};

        SDL_RenderCopyExF(m_renderer, texture, NULL, &rect, 0, NULL, SDL_RendererFlip());

        SDL_DestroyTexture( texture );
        SDL_FreeSurface( text_surface );
        count++;
    }



 
}
