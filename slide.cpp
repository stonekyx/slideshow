#include <iostream>

#include "util.h"
#include "slide.h"

using namespace Slideshow;
using namespace std;

int Slide::run(SDL_Window *window, SDL_Renderer *renderer)
{
    if(finished) {
        finished = false;
        return -2;
    }
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    finished = true;
    return -1;
}

Slide::Slide()
{
    finished = false;
}

bool Slide::explain(vector<string> prms, Instruction *&inst)
{
    if(prms[0].compare("newpage")==0) {
        inst = new Slide();
        return true;
    }
    return false;
}

extern "C"
Slide::explain_t get_explain()
{
    return Slide::explain;
}
