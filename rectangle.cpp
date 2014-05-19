#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "rectangle.h"

using namespace Slideshow;
using namespace std;

int InstRect::run(SDL_Window *window, SDL_Renderer *renderer)
{
    if(finished) {
        finished = false;
        return -2;
    }
    cout<<"Got rect"<<endl;
    //TODO: graphical context
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &this->rect);
    SDL_RenderPresent(renderer);
    finished = true;
    return -1;
}

InstRect::InstRect()
{
    finished = false;
}

bool InstRect::explain(vector<string> prms, Instruction *&inst)
{
    if(prms[0].compare("rect")) {
        return false;
    }
    InstRect *res = new InstRect();
    res->rect.x = boost::lexical_cast<int>(prms[1]);
    res->rect.y = boost::lexical_cast<int>(prms[2]);
    res->rect.w = boost::lexical_cast<int>(prms[3]);
    res->rect.h = boost::lexical_cast<int>(prms[4]);
    inst = res;
    return true;
}

extern "C"
InstRect::explain_t get_explain()
{
    return InstRect::explain;
}
