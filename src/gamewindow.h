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

struct Edge {
    int src, dest, weigth;
};


struct PanelParams {
    bool _airplane_selector_open = false, _airport_selector_open = false, _need_panel_update = false;
};

class Ressource {
    private: 
        std::string m_path;
        SDL_Surface* m_ressource = NULL;
        Display m_display;
        Element m_element = Element::IMAGE;
        int m_width, m_height;
        int m_init_x, m_init_y;
        int m_relative_x, m_relative_y;
        bool m_clickable = true, m_renderable = true;
    public: 
        Ressource(std::string _path, Display _display, int _width, int _height, int _x, int _y) : m_path(_path), m_display(_display), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y) {
            init();
        }

        Ressource(std::string _path, Display _display, int _width, int _height, int _x, int _y, bool _clickable) : m_path(_path), m_display(_display), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y), m_clickable(_clickable) {
            init();
        }

        Ressource(std::string _path, Display _display, Element _element, int _width, int _height, int _x, int _y, bool _clickable) : m_path(_path), m_display(_display), m_element(_element), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y), m_clickable(_clickable) {
            init();
        }

        void init() {

            m_relative_x = m_init_x;
            m_relative_y = m_init_y;
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
            if (m_element == Element::IMAGE) {
                setSurface(IMG_Load(getPath().c_str()));
                
            } else if (m_element == Element::TEXT || m_element == Element::SELECTOR_AIRPLANE || m_element == Element::SELECTOR_AIRPORT) {
                std::cout << "debbbug";
                if (m_element == Element::SELECTOR_AIRPLANE || m_element == Element::SELECTOR_AIRPORT) {
                    setClickable(false);
                    setRenderable(false);
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
        std::string getPath() const { return m_path; }
        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        int getX() const { return m_init_x; }
        int getY() const { return m_init_y; }
        int getRelativeX() const { return m_init_x; }
        int getRelativeY() const { return m_init_y; }
        bool isClickable() const { return m_clickable; }
        bool isRenderable() const { return m_renderable; }
        Display getDisplay() const { return m_display; }
        Element getElement() const { return m_element; }

        //Setters
        void setWidth( int width ) { m_width = width; };
        void setHeight( int height ) { m_height = height; };
        void setX( int x ) { m_init_x = x; };
        void setY( int y ) { m_init_y = y; };
        void setClickable(bool _clickable) { m_clickable = _clickable; }
        void setRenderable(bool _renderable) { m_renderable = _renderable; }

        ~Ressource() {}
        SDL_Surface* getSurface() { return m_ressource; }
        void setSurface(SDL_Surface* _surface) { m_ressource = _surface; }
};

class GameWindow {
    private:
        std::string m_window_name;
        int m_screen_width, m_screen_height;
        SDL_Window* m_window = NULL;
        SDL_Renderer* m_render = NULL;
        SDL_Surface* m_surface = NULL;
        std::vector<Ressource> m_ressources;
        std::vector<std::pair<SDL_Texture*, SDL_Rect>> m_textures;
        AerialNetwork m_aerialnetwork = AerialNetwork();
        Airplane m_current_airplane;
        Airport m_current_airport;
        std::vector<Edge> m_edges;
        Graph m_graph;

    public:
        // Constructors & Destructor
        GameWindow(std::string _window_name, int _screen_width, int _screen_height) : 
            m_window_name(_window_name), m_screen_width(_screen_width), m_screen_height(_screen_height) {}
        ~GameWindow() {}

        // Getters
        SDL_Window* getWindow() const { return m_window; }
        SDL_Renderer* getRender() const { return m_render; }
        int getWidth() const { return m_screen_width; }
        int getHeight() const { return m_screen_height; }
        SDL_Surface* getSurface() const { return m_surface; }
        std::string getWindowName() const { return  m_window_name; }
        std::vector<Ressource>& getRessources() { return m_ressources; }
        std::vector<std::pair<SDL_Texture*, SDL_Rect>>& getTextures() { return m_textures; }
        AerialNetwork getAerialNetwork() const { return m_aerialnetwork; }
        Airplane get_current_airplane() const { return m_current_airplane; }
        Airport get_current_airport() const { return m_current_airport; }
        std::vector<Edge>& get_edges() { return m_edges; }
        Graph& get_graph() { return m_graph; }

        // Setters
        void setWindow(SDL_Window* _window) { m_window = _window; } 
        void setRender(SDL_Renderer* _render) { m_render = _render;}
        void setSurface(SDL_Surface* _surface) { m_surface = _surface; }
        void setAerialNetwork(AerialNetwork _aerialnetwork) { m_aerialnetwork = _aerialnetwork; }
        void set_current_airplane(Airplane _current_airplane) { m_current_airplane = _current_airplane; }
        void set_current_airport(Airport _current_airport) { m_current_airport = _current_airport; }

        // Methods
        bool init();
        bool loadMedia(std::string _path_image);
        void close();
        void menu();
        void cursor_move(int choice);
        void run(std::string _path_image);

        void render(bool update_edges);
        void render_edges();

        void addRessource(Ressource _rsc) { m_ressources.push_back(_rsc); }
        bool isRessourceClicked(int _x, int _y);
        Ressource* getRessourceClicked(int _x, int _y);
        void updateTextures();
        void updateTexture(std::string _path);

        // Visual
        std::vector<Edge> drawGraph(Graph graph);

        // Handling events
        void handlePanels(Ressource* _clicked_ressource, PanelParams* _params);
};

#endif // GAMEWINDOW_H_INCLUDED