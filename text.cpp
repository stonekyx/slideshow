#include <iostream>

#include <boost/lexical_cast.hpp>

#include <SDL_ttf.h>

#include "util.h"
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
    SDL_SetColorKey(text_sur, SDL_TRUE, SDL_MapRGB(text_sur->format, 255, 255, 255));
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(gc.renderer, text_sur);
    SDL_QueryTexture(text_texture, NULL, NULL,
            &this->w, &this->h);
    int x, y;
    this->get_point(&x, &y);
    this->x = boost::lexical_cast<string>(x);
    this->y = boost::lexical_cast<string>(y);
    SDL_Rect rect = get_rect_from_pos(x, y, text_texture);
    SDL_SetTextureBlendMode(text_texture, SDL_BLENDMODE_NONE);
    SDL_RenderCopy(gc.renderer, text_texture, NULL, &rect);
    SDL_RenderPresent(gc.renderer);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_sur);
    TTF_CloseFont(font);
    finished = true;
    return -1;
}

bool InstText::runback(GContext &gc)
{
    finished = false;
    return false;
}

void InstText::get_point(int *x, int *y)
{
    *x = this->parse_coor(this->x);
    *y = this->parse_coor(this->y);
}

void InstText::get_size(int *w, int *h)
{
    *w = this->w;
    *h = this->h;
}

InstText::InstText() : finished(false)
{
}

bool InstText::explain(vector<string> prms, Instruction *&inst)
{
    if(prms.size()<4 || prms[0].compare("text")) {
        return false;
    }
    InstText *res = new InstText();
    res->x = prms[1];
    res->y = prms[2];
    res->text = prms[3];
    inst = res;
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
