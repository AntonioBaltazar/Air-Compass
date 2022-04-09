#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "aerialnetwork.h"

namespace Utils {
    Airport* get_airport(int _num) {
        AerialNetwork an;
        an.create_fleet();
        if(_num >= 0 && _num < an.get_airports().size())
            return &an.get_airports()[_num];
        return NULL;
    }
};

#endif // SUTILS_H_INCLUDED