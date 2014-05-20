#include <iostream>

#include <boost/lexical_cast.hpp>

#include <SDL_ttf.h>

#include "text.h"

using namespace Slideshow;
using namespace std;

int InstText::run(GContext &gc)
{
    if(finished) {
        finished = false;
        return -2;
    }
    cout<<"Got text"<<endl;
    TTF_Font *font = TTF_OpenFont(gc.font_family.c_str(), gc.font_size);
    SDL_Surface *text_sur = TTF_RenderUTF8_Shaded(font, text.c_str(), gc.fg, gc.bg);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(gc.renderer, text_sur);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(text_texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(gc.renderer, text_texture, NULL, &rect);
    SDL_RenderPresent(gc.renderer);
    finished = true;
    return -1;
}

InstText::InstText(int x, int y, const string &text) :
    finished(false), text(text), x(x), y(y)
{
}

bool InstText::explain(vector<string> prms, Instruction *&inst)
{
    if(prms.size()<4 || prms[0].compare("text")) {
        return false;
    }
    inst = new InstText(boost::lexical_cast<int>(prms[1]),
            boost::lexical_cast<int>(prms[2]), prms[3]);
    return true;
}

extern "C"
InstText::explain_t get_explain()
{
    return InstText::explain;
}

static void lib_init() __attribute__((constructor));
static void lib_exit() __attribute__((destructor));

void lib_init()
{
    if(!TTF_WasInit()) {
        TTF_Init();
    }
}

void lib_exit()
{
    if(TTF_WasInit()) {
        TTF_Quit();
    }
}
