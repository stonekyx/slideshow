#ifndef UTIL_H

// Functions in this unit will be exported from core, so plugins are free to
// use them.

#define UTIL_H

#include <SDL.h>

#include "gcontext.h"

namespace Slideshow {
    //SDLK_UNKNOWN for any key
    //return SDLK_UNKNOWN(i.e. 0) on normal exit, -1 on error,
    //or a SDL_Keycode received when argument is SDLK_UNKNOWN.
    int wait_key(SDL_Keycode);
    SDL_Rect get_rect_from_pos(int x, int y, SDL_Texture *);
}

#endif
