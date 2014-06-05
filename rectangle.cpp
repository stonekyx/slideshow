#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "rectangle.h"

using namespace Slideshow;
using namespace std;

int InstRect::run(GContext &gc)
{
    if(finished) {
        finished = false;
        return -2;
    }
    cout<<"Got rect"<<endl;
    SDL_Rect rect;
    this->get_point(&rect.x, &rect.y);
    this->get_size(&rect.w, &rect.h);
    this->x = boost::lexical_cast<string>(rect.x);
    this->y = boost::lexical_cast<string>(rect.y);
    this->w = boost::lexical_cast<string>(rect.w);
    this->h = boost::lexical_cast<string>(rect.h);
    SDL_SetRenderDrawColor(gc.renderer,
            gc.fg.r, gc.fg.g, gc.fg.b, gc.fg.a);
    SDL_RenderFillRect(gc.renderer, &rect);
    SDL_RenderPresent(gc.renderer);
    finished = true;
    return this->delay;
}

bool InstRect::runback(GContext &gc)
{
    finished = false;
    return false;
}

void InstRect::get_point(int *x, int *y)
{
    *x = Instruction::parse_coor(this->x);
    *y = Instruction::parse_coor(this->y);
}

void InstRect::get_size(int *w, int *h)
{
    *w = Instruction::parse_coor(this->w);
    *h = Instruction::parse_coor(this->h);
}

InstRect::InstRect()
{
    finished = false;
}

bool InstRect::explain(vector<string> prms, Instruction *&inst)
{
    if(prms.size()<5 || prms[0].compare("rect")) {
        return false;
    }
    InstRect *res = new InstRect();
    res->x = prms[1];
    res->y = prms[2];
    res->w = prms[3];
    res->h = prms[4];
    inst = res;
    return true;
}

extern "C"
InstRect::explain_t get_explain()
{
    return InstRect::explain;
}
