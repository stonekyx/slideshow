#ifndef UTIL_H

// Functions in this unit will be exported from core, so plugins are free to
// use them.

#define UTIL_H

#include <string>

#include <SDL.h>

#include "gcontext.h"

namespace Slideshow {
    //SDLK_UNKNOWN for any key
    //return SDLK_UNKNOWN(i.e. 0) on normal exit, -1 on error,
    //or a SDL_Keycode received when argument is SDLK_UNKNOWN.
    int wait_key(SDL_Keycode);
    SDL_Keycode wait_key_timeout(int);
    SDL_Rect get_rect_from_pos(int x, int y, SDL_Texture *);
    void clear_with_bg(GContext &, SDL_Rect *rect);
    void clear_with_bg(GContext &, int x, int y, int w, int h);
    void get_full_fontpath(std::string &);
    void reduce_spaces(std::string &);
}

#endif
