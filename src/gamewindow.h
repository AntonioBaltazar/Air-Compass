#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <SDL2/SDL.h>

class GameWindow {
    private:
        std::string m_window_name;
        int m_screen_width, m_screen_height;
        SDL_Window* m_window = NULL;
        SDL_Surface* m_surface = NULL;
        SDL_Surface* m_image = NULL;
    public:
        // Constructors & Destructor
        GameWindow(std::string _window_name, int _screen_width, int _screen_height) : 
            m_window_name(_window_name), m_screen_width(_screen_width), m_screen_height(_screen_height) {}
        ~GameWindow() {}

        // Getters
        SDL_Window* getWindow() const { return m_window; }
        SDL_Surface* getSurface() const { return m_surface; }
        SDL_Surface* getImage() const { return m_image; }
        int getWidth() const { return m_screen_width; }
        int getHeight() const { return m_screen_height; }
        std::string getWindowName() const { return  m_window_name; }

        // Setters
        void setWindow(SDL_Window* _window) { m_window = _window; }
        void setSurface(SDL_Surface* _surface) { m_surface = _surface; }
        void setImage(SDL_Surface* _image) { m_image = _image; }

        // Methods
        bool init();
        bool loadMedia(std::string _path_image);
        bool close();
        void run(std::string _path_image);
        SDL_Surface* resizeImage(int w,int h,SDL_Surface* src);
};

#endif // GAMEWINDOW_H_INCLUDED