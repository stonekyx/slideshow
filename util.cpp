#include <ctime>

#include "util.h"

using namespace Slideshow;
using namespace std;

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

SDL_Keycode Slideshow::wait_key_timeout(int timeout)
{
    const long long e3 = 1e3, e6 = 1e6, e9 = 1e9;
    SDL_Event e;
    struct timespec tar;
    if(-1==clock_gettime(CLOCK_MONOTONIC, &tar)) {
        SDL_Delay(timeout);
        return SDLK_UNKNOWN;
    }
    tar.tv_sec += ((long long)tar.tv_nsec+timeout*e6)/e9;
    tar.tv_nsec = ((long long)tar.tv_nsec+timeout*e6)%e9;
    while(true) {
        int curwait;
        struct timespec now;
        if(-1==clock_gettime(CLOCK_MONOTONIC, &now)) {
            return SDLK_UNKNOWN;
        }
        curwait = (tar.tv_sec - now.tv_sec)*e3 +
            (tar.tv_nsec - now.tv_nsec)/e6;
        if(SDL_WaitEventTimeout(&e, curwait)==0) {
            return SDLK_UNKNOWN;
        }
        if(e.type==SDL_KEYDOWN) {
            return e.key.keysym.sym;
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

void Slideshow::get_full_fontpath(string &font)
{
    while(font.find('/')==font.npos) {
        const char *fontdir = getenv("FONTDIR");
        if(fontdir) {
            string dir(fontdir);
            dir+="/";
            dir+=font;
            font = dir;
            break;
        }
        const char *home = getenv("HOME");
        if(home) {
            string dir(home);
            dir+="/.fonts/";
            dir+=font;
            font = dir;
            break;
        }
    }
}

void Slideshow::reduce_spaces(string &str)
{
    bool off=false;
    for(unsigned int i=0; i<str.length();) {
        if(str[i]=='\\') {
            i+=2; continue;
        }
        if(str[i]=='"') {
            off=!off;
        }
        if(i==0 || str[i-1]!=' ' || str[i]!=' ' || off) {
            i++; continue;
        }
        str.erase(i, 1);
    }
}
