#include "util.h"

using namespace Slideshow;

int Slideshow::wait_key(SDL_Keycode kc)
{
    SDL_Event e;
    while(true) {
        if(SDL_WaitEvent(&e)==0) {
            return -1;
        }
        if(e.type==SDL_KEYDOWN &&
                (e.key.keysym.sym==kc || kc==SDLK_UNKNOWN)) {
            return kc==SDLK_UNKNOWN ?
                e.key.keysym.sym : SDLK_UNKNOWN;
        }
    }
}

SDL_Rect Slideshow::get_rect_from_pos(int x, int y, SDL_Texture *texture)
{
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = x;
    rect.y = y;
    return rect;
}
