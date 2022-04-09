#include <iostream>
#include "gamewindow.h"

using namespace std;

void Ressource::setSurface(SDL_Surface* _surface) { 
    if (getElement() == Element::TEXT || getElement() == Element::SELECTOR_AIRPLANE 
    || getElement() == Element::SELECTOR_AIRPORT) {
        m_width = _surface->w;
        m_height = _surface->h;
        update_display();
    }
    m_ressource = _surface;
}

void Ressource::update_display() {
            switch (m_display) {
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

void Ressource::init() {
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

Ressource::Ressource(std::string _path, Display _display, int _width, int _height, int _x, int _y, Event_Config _event_config) : m_path(_path), m_display(_display), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y), m_event_config(_event_config) {
    init();
}

Ressource::Ressource(std::string _path, Display _display, Element _element, int _width, int _height, int _x, int _y, Event_Config _event_config) : m_path(_path), m_display(_display), m_element(_element), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y), m_event_config(_event_config) {
    init();
}

Ressource::Ressource(std::string path) : m_path (path) {};

Ressource::Ressource(std::string _path, Display _display, int _width, int _height, int _x, int _y)
    : m_path(_path), m_display(_display), m_width(_width), m_height(_height), m_init_x(_x), m_init_y(_y) {
    init();
}

Ressource::Ressource(Element _element, std::string _text, std::string _font, int _font_size, Display _display, int _x, int _y, SDL_Color _default, SDL_Color _hover, SDL_Color _active) 
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