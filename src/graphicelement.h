#ifndef GRAPHICELEMENT_H_INCLUDED
#define GRAPHICELEMENT_H_INCLUDED

#include <string>
#include <SDL2/SDL.h>


struct coord
{
    int x;
    int y;
};

class GraphicElement{
    private:
        coord m_coordinates;
        std::string m_path;
        //Fonction appelé lors du clic
    public:

        ///Constructor and Destructor
        GraphicElement() {};
        ~GraphicElement() {};

        ///Getter
        coord get_coordinate() const { return m_coordinates; } ;
        std::string get_path() const { return m_path; } ;

        ///Setter
        void set_coordinate(coord _coordinate) {m_coordinates = _coordinate ; } ;
        void set_path(std::string _path) {m_path = _path ; } ;

        ///Methods
};

void handle_event();
bool mouse_coordinates(SDL_Event event, int x1, int x2, int y1, int y2);

#endif // GRAPHICELEMENT_H_INCLUDED