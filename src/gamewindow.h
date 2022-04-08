#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
#include "aerialnetwork.h"
#include "graph.h"

enum class Display { TOP_LEFT, TOP_RIGHT, CENTER, BOTTOM_LEFT, BOTTOM_RIGHT};
enum class Element { SELECTOR_AIRPLANE, SELECTOR_AIRPORT, AIRPORT, TEXT, BACKGROUND, DEFAULT, IMAGE };
enum class State { RUNNING, LEAVING, SIMULATE, CONFIG };

struct Edge {
    int src, dest, weigth;
};

struct PanelParams {
    bool _airplane_selector_open = false, _airport_selector_open = false, _need_panel_update = false;
};

struct GraphParams {
    bool _need_edges_update = false;
};

struct Color {

};

struct Text_Params {
    int _font_size;
    std::string _font, _text;
    SDL_Color _default_color;
    SDL_Color _hover_color;
    SDL_Color _active_color;
};

struct Event_Config {
    bool _clickable = true, _renderable = true;
};

class Ressource {
    private: 
        Element m_element = Element::IMAGE;
        int m_init_x, m_init_y;
        Display m_display;

        int m_width, m_height;

        std::string m_path;
        SDL_Surface* m_ressource = NULL;
        int m_relative_x, m_relative_y;

        // New params
        Text_Params m_text_params;
        Event_Config m_event_config;

        
    public: 

        // New ressource
        // Text ressource
        Ressource(Element _element, std::string _text, std::string _font, int _font_size, Display _display, int _x, int _y, SDL_Color _default, SDL_Color _hover, SDL_Color _active) 
            : m_element(_element), m_init_x(_x), m_init_y(_y), m_display(_display) {
            m_text_params._text = _text;
            m_text_params._font = _font;
            m_text_params._font_size = _font_size;
            m_text_params._default_color = _default;
            m_text_params._hover_color = _hover;
            m_text_params._active_color = _active;
            
            update_display();
            
            TTF_Init();
            TTF_Font* font = TTF_OpenFont(("rsc/fonts/" + std::string(get_text_params()._font) + ".ttf").c_str(), get_text_params()._font_size);
            if (font != NULL)
                setSurface(TTF_RenderText_Blended(font, get_text_params()._text.c_str(), get_text_params()._default_color));
            TTF_CloseFont(font);
            if (_element == Element::SELECTOR_AIRPLANE || _element == Element::SELECTOR_AIRPORT)
                get_event_config() = {true, false};
        }

        Ressource(std::string _path, Display _display, int _width, int _height, int _x, int _y) : m_path(_path), m_display(_display), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y) {
            init();
        }

        Ressource(std::string _path, Display _display, int _width, int _height, int _x, int _y, Event_Config _event_config) : m_path(_path), m_display(_display), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y), m_event_config(_event_config) {
            init();
        }

        Ressource(std::string _path, Display _display, Element _element, int _width, int _height, int _x, int _y, Event_Config _event_config) : m_path(_path), m_display(_display), m_element(_element), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y), m_event_config(_event_config) {
            init();
        }
        Ressource(std::string path) : m_path (path) {};

        void init() {
            m_relative_x = m_init_x;
            m_relative_y = m_init_y;
            update_display();
            SDL_Init( SDL_INIT_VIDEO );
            if (m_element == Element::IMAGE) {
                IMG_Init(IMG_INIT_JPG);
                setSurface(IMG_Load(getPath().c_str()));
                IMG_Quit();
            } else if (m_element == Element::TEXT || m_element == Element::SELECTOR_AIRPLANE || m_element == Element::SELECTOR_AIRPORT) {
               
                if (m_element == Element::SELECTOR_AIRPLANE || m_element == Element::SELECTOR_AIRPORT) {
                    get_event_config() = {false, false};

                }
                if (TTF_Init() < 0) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
                    return;
                }
                TTF_Font* font = TTF_OpenFont("rsc/fonts/SFPro_Regular.ttf", 18);
                if (font == nullptr) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "#1 [DEBUG] > %s", TTF_GetError());
                setSurface(TTF_RenderText_Blended(font, getPath().c_str(), SDL_Color{255, 255, 255, 255}));
                setWidth(getSurface()->w);
            }
            
        }

        //Getters
        Text_Params& get_text_params() { return m_text_params; }
        Event_Config& get_event_config() { return m_event_config; }


        std::string getPath() const { return m_path; }
        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        int getX() const { return m_init_x; }
        int getY() const { return m_init_y; }
        int getRelativeX() const { return m_relative_x; }
        int getRelativeY() const { return m_relative_y; }
        Display getDisplay() const { return m_display; }
        Element getElement() const { return m_element; }

        //Setters
        void setPath( std::string path) { m_path = path;  }
        void setWidth( int width ) { m_width = width; };
        void setHeight( int height ) { m_height = height; };
        void setX( int x ) { m_init_x = x; };
        void setY( int y ) { m_init_y = y; };
        ~Ressource() {}
        SDL_Surface* getSurface() { return m_ressource; }
        void setSurface(SDL_Surface* _surface) { 
            if (getElement() == Element::TEXT || getElement() == Element::SELECTOR_AIRPLANE 
            || getElement() == Element::SELECTOR_AIRPORT) {
                m_width = _surface->w;
                m_height = _surface->h;
                update_display();
            }
            m_ressource = _surface;
        }

        void update_display() {
            switch (getDisplay()) {
                case Display::CENTER:
                    m_relative_x = getX() - getWidth()/2;
                    m_relative_y = getY() - getHeight()/2;
                    break;
                case Display::TOP_LEFT:
                    m_relative_x  = getX();
                    m_relative_y = getY();
                    break;
                case Display::TOP_RIGHT:
                    m_relative_x  = getX() + getWidth();
                    m_relative_y = getY();
                    break;
                case Display::BOTTOM_LEFT:
                    m_relative_x  = getX();
                    m_relative_y = getY() + getHeight();
                    break;
                case Display::BOTTOM_RIGHT:
                    m_relative_x  = getX() + getWidth();
                    m_relative_y = getY() + getHeight();
                    break;
                default: break;
            }
        }
};

class GameWindow {
    private:
        // Ce qu'on a vraiment besoin
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        int m_screen_width, m_screen_height;
        

        // A traiter
        std::string m_window_name;
       
        std::vector<Ressource> m_ressources;
        std::vector<std::pair<SDL_Texture*, SDL_Rect>> m_textures;
        AerialNetwork m_aerialnetwork = AerialNetwork();
        Airplane m_current_airplane;
        Airport m_current_airport;
        std::vector<Edge> m_edges;
        Graph m_graph, m_displayed_graph;
        GraphParams m_graph_params;
        bool m_need_render;
    public:
        // Constructors & Destructor
        GameWindow(std::string _window_name, int _screen_width, int _screen_height) : m_screen_width(_screen_width), m_screen_height(_screen_height) {
            SDL_Init(SDL_INIT_EVERYTHING);
            SDL_CreateWindowAndRenderer(m_screen_width, m_screen_height, SDL_WINDOW_SHOWN, &m_window, &m_renderer);        
            SDL_SetWindowTitle(m_window, _window_name.c_str());
            TTF_Init();
       }

        ~GameWindow() {
            std::cout << "Destructing GameWindow";
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
        }

        // Getters
        SDL_Window* getWindow() const { return m_window; }
        SDL_Renderer* getRender() const { return m_renderer; }
        int getWidth() const { return m_screen_width; }
        int getHeight() const { return m_screen_height; }

        std::string getWindowName() const { return  m_window_name; }
        std::vector<Ressource>& getRessources() { return m_ressources; }
        std::vector<std::pair<SDL_Texture*, SDL_Rect>>& getTextures() { return m_textures; }
        AerialNetwork getAerialNetwork() const { return m_aerialnetwork; }
        Airplane get_current_airplane() const { return m_current_airplane; }
        Airport get_current_airport() const { return m_current_airport; }
        std::vector<Edge>& get_edges() { return m_edges; }
        Graph& get_graph() { return m_graph; }
        Graph& get_displayed_graph() { m_displayed_graph; }
        GraphParams& get_graph_params() { return m_graph_params; }

        // Setters
        void setWindow(SDL_Window* _window) { m_window = _window; } 
        void setRender(SDL_Renderer* _renderer) { m_renderer = _renderer;}

        void setAerialNetwork(AerialNetwork _aerialnetwork) { m_aerialnetwork = _aerialnetwork; }
        void set_current_airplane(Airplane _current_airplane) { m_current_airplane = _current_airplane; }
        void set_current_airport(Airport _current_airport) { m_current_airport = _current_airport; }

        // Methods
        bool loadMedia(std::string _path_image);     

        // Differents states of simulation
        void launch();
        void run();

        void render();
        void render_edges();

        void addRessource(Ressource _rsc) { m_ressources.push_back(_rsc); }
        bool isRessourceClicked(int _x, int _y);
        Ressource* getRessourceClicked(int _x, int _y);
        Ressource* getRessourceClicked2(int _x, int _y);
        void updateTextures();
        void updateTexture(std::string _path);

        // Algorithm
        void updateGraph(); 

        // Visual
        std::vector<Edge> drawGraph(Graph graph);

        // Handling events
        void handlePanels(Ressource* _clicked_ressource, PanelParams* _params);
        State handle_click_on_menu(Ressource* _clicked_ressource);
};

#endif // GAMEWINDOW_H_INCLUDED