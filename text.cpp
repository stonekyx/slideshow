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
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(gc.renderer, text_sur);
    int x, y;
    this->get_point(&x, &y);
    SDL_Rect rect = get_rect_from_pos(x, y, text_texture);
    SDL_RenderCopy(gc.renderer, text_texture, NULL, &rect);
    SDL_RenderPresent(gc.renderer);
    finished = true;
    return -1;
}

void InstText::get_point(int *x, int *y)
{
    *x = Instruction::parse_coor(this->x);
    *y = Instruction::parse_coor(this->y);
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
