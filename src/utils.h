#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "database.h"

namespace Utils {
    Airport* get_airport(int _num) {
        Database an(true);
        
        if(_num >= 0 && _num < an.get_airports().size())
            return &an.get_airports()[_num];
        return NULL;
    }
    SDL_Texture* IMG_LoadTexture(SDL_Renderer* renderer, std::string file) {
        SDL_Texture *texture = NULL;
        SDL_Surface *surface = IMG_Load(file.c_str());
        if (surface) {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
        return texture;
    }
};

#endif // SUTILS_H_INCLUDED