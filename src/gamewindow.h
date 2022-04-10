#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <vector>
#include <iostream>
#include "graph.h"
#include "simulation.h"
#include "database.h"
<<<<<<< HEAD
#include "audio.h"
=======
>>>>>>> cf1f04c004d466556d7d906a952b62649bae7a0f

enum class Display { TOP_LEFT, TOP_RIGHT, CENTER, BOTTOM_LEFT, BOTTOM_RIGHT};
enum class Element { SELECTOR_AIRPLANE, SELECTOR_AIRPORT, AIRPORT, TEXT, BACKGROUND, DEFAULT, IMAGE };
enum class State { RUNNING, LEAVING, SIMULATE, CONFIG, CREDIT};


struct PanelParams {
    bool _airplane_selector_open = false, _airport_selector_open = false, _need_panel_update = false;
};

struct GraphParams {
    bool _need_edges_update = false;
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
        // Constructors & Destructor
        Ressource(Element _element, std::string _text, std::string _font, int _font_size, Display _display, int _x, int _y, SDL_Color _default, SDL_Color _hover, SDL_Color _active);
        Ressource(std::string _path, Display _display, int _width, int _height, int _x, int _y);
        Ressource(std::string _path, Display _display, int _width, int _height, int _x, int _y, Event_Config _event_config);
        Ressource(std::string _path, Display _display, Element _element, int _width, int _height, int _x, int _y, Event_Config _event_config);
        Ressource(std::string path);

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
        void setSurface(SDL_Surface* _surface);

        // Methods
        void update_display();
        void init();
};

class GameWindow {
    private:
        // Ce qu'on a vraiment besoin
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        int m_screen_width, m_screen_height;
        std::vector<Ressource> m_ressources;
        std::vector<std::pair<SDL_Texture*, SDL_Rect>> m_textures;
        Database m_aerialnetwork = Database(true);
        Airplane m_current_airplane;
        Airport m_current_airport;
        std::vector<Edge> m_edges;
        Graph m_graph, m_displayed_graph;
        GraphParams m_graph_params;
        bool m_need_render;

        Simulation m_simulation;
    public:
        // Constructors & Destructor
        GameWindow(std::string _window_name, int _screen_width, int _screen_height) : m_screen_width(_screen_width), m_screen_height(_screen_height) {
            SDL_Init(SDL_INIT_EVERYTHING);
            SDL_CreateWindowAndRenderer(m_screen_width, m_screen_height, SDL_WINDOW_SHOWN, &m_window, &m_renderer);        
            SDL_SetWindowTitle(m_window, _window_name.c_str());

            TTF_Init();
            SDL_Init(SDL_INIT_AUDIO);

            // Initialize Simple-SDL2-Audio
            initAudio();
       }

        ~GameWindow() {
            std::cout << "Destructing GameWindow";
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
        }

        // Getters
        Database& getAerialNetwork() { return m_aerialnetwork; }

        std::vector<Edge>& get_edges() { return m_edges; }
        Graph& get_graph() { return m_graph; }
        Graph& get_displayed_graph() { m_displayed_graph; }
        GraphParams& get_graph_params() { return m_graph_params; }

        // Setters
        void setWindow(SDL_Window* _window) { m_window = _window; } 
        void setRender(SDL_Renderer* _renderer) { m_renderer = _renderer;}

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
        void render_simulation();
        std::vector<Edge> drawGraph(Graph graph);
        int display_credits();

        // Handling events
        void handlePanels(Ressource* _clicked_ressource, PanelParams* _params);
        State handle_click_on_menu(Ressource* _clicked_ressource);

        void play_sound(std::string _music_name, int _volume, bool _loop);
};

#endif // GAMEWINDOW_H_INCLUDED