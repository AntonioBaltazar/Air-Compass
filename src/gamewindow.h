#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

enum class Display { TOP_LEFT, TOP_RIGHT, CENTER, BOTTOM_LEFT, BOTTOM_RIGHT};

class Ressource {
    private: 
        SDL_Surface* m_ressource = NULL;
        int m_width, m_height;
        int m_init_x, m_init_y;
        int m_relative_x, m_relative_y;
        std::string m_path;
        Display m_display;
        bool m_clickable = true;

    public: 
        Ressource(std::string _path, Display _display, int _width, int _height, int _x, int _y) : m_path(_path), m_display(_display), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y) {
            init();
        }
        Ressource(std::string _path, Display _display, int _width, int _height, int _x, int _y, bool _clickable) : m_path(_path), m_display(_display), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y), m_clickable(_clickable) {
            init();
        }

        void init() {
            setSurface(IMG_Load(getPath().c_str()));
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

        //Getters
        std::string getPath() const { return m_path; }
        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        int getX() const { return m_init_x; }
        int getY() const { return m_init_y; }
        int getRelativeX() const { return m_init_x; }
        int getRelativeY() const { return m_init_y; }
        bool isClickable() const { return m_clickable; }
        Display getDisplay() const { return m_display; }

        //Setters
        void setWidth( int width ) { m_width = width; };
        void setHeight( int height ) { m_height = height; };
        void setX( int x ) { m_init_x = x; };
        void setY( int y ) { m_init_y = y; };

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

        // Setters
        void setWindow(SDL_Window* _window) { m_window = _window; }
 
        void setRender(SDL_Renderer* _render) { m_render = _render;}
        void setSurface(SDL_Surface* _surface) { m_surface = _surface; }
    

        // Methods
        bool init();
        bool loadMedia(std::string _path_image);
        void close();
        void menu();
        void cursor_move();
        void run(std::string _path_image);

        void addRessource(Ressource _rsc) { m_ressources.push_back(_rsc); }
        bool isRessourceClicked(int _x, int _y);
};

#endif // GAMEWINDOW_H_INCLUDED