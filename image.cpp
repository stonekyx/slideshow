#include <iostream>

#include <SDL_image.h>
#include <boost/lexical_cast.hpp>

#include "image.h"

using namespace Slideshow;
using namespace std;

void InstImg::run(SDL_Window *window, SDL_Renderer *renderer)
{
    cout<<"Got image"<<endl;
    SDL_Texture *img = IMG_LoadTexture(renderer, path.c_str());
    SDL_Rect rect;
    rect.x = x; rect.y = y;
    SDL_QueryTexture(img, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, img, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}

bool InstImg::explain(vector<string> prms, Instruction *&inst)
{
    if(prms[0].compare("img")) {
        return false;
    }
    InstImg *res = new InstImg();
    res->x = boost::lexical_cast<int>(prms[1]);
    res->y = boost::lexical_cast<int>(prms[2]);
    res->path = prms[3];
    inst = res;
    return true;
}

extern "C"
InstImg::explain_t get_explain()
{
    return InstImg::explain;
}
