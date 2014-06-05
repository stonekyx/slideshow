#include <iostream>

#include <SDL_image.h>
#include <boost/lexical_cast.hpp>

#include "image.h"

using namespace Slideshow;
using namespace std;

int InstImg::run(GContext &gc)
{
    if(finished) {
        finished = false;
        return -2;
    }
    cout<<"Got image"<<endl;
    SDL_Texture *img = IMG_LoadTexture(gc.renderer, path.c_str());
    SDL_Rect rect;
    this->get_point(&rect.x, &rect.y);
    this->x = boost::lexical_cast<string>(rect.x);
    this->y = boost::lexical_cast<string>(rect.y);
    SDL_QueryTexture(img, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(gc.renderer, img, NULL, &rect);
    SDL_RenderPresent(gc.renderer);
    SDL_DestroyTexture(img);
    finished = true;
    return this->delay;
}

bool InstImg::runback(GContext &gc)
{
    finished = false;
    return false;
}

void InstImg::get_point(int *x, int *y)
{
    *x = Instruction::parse_coor(this->x);
    *y = Instruction::parse_coor(this->y);
}

void InstImg::get_size(int *w, int *h)
{
    SDL_Surface *img = IMG_Load(this->path.c_str());
    *w = img->w;
    *h = img->h;
    SDL_FreeSurface(img);
}

InstImg::InstImg()
{
    finished = false;
}

bool InstImg::explain(vector<string> prms, Instruction *&inst)
{
    if(prms.size()<4 || prms[0].compare("img")) {
        return false;
    }
    InstImg *res = new InstImg();
    res->x = prms[1];
    res->y = prms[2];
    res->path = prms[3];
    inst = res;
    return true;
}

extern "C"
InstImg::explain_t get_explain()
{
    return InstImg::explain;
}
