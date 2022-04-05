#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Ressource {
    private: 
        SDL_Surface* m_ressource = NULL;
        int m_width, m_height;
        int m_init_x, m_init_y;
        std::string m_path;
    public: 
        Ressource(std::string _path, int _width, int _height, int _x, int _y) : m_path(_path), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y) {
            setSurface(IMG_Load(m_path.c_str()));
        }

        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        int getX() const { return m_init_x; }
        int getY() const { return m_init_y; }

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
        bool close();
        void run(std::string _path_image);

        void addRessource(Ressource _rsc) { m_ressources.push_back(_rsc); }
   
};

#endif // GAMEWINDOW_H_INCLUDED