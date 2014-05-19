#ifndef UTIL_H

#define UTIL_H

#include <SDL.h>

namespace Slideshow {
    //SDLK_UNKNOWN for any key
    //return SDLK_UNKNOWN(i.e. 0) on normal exit, -1 on error,
    //or a SDL_Keycode received when argument is SDLK_UNKNOWN.
    int wait_key(SDL_Keycode);
}

#endif
