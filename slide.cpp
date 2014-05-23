#include <iostream>

#include "util.h"
#include "slide.h"

using namespace Slideshow;
using namespace std;

int Slide::run(GContext &gc)
{
    if(finished) {
        finished = false;
        return -2;
    }
    SDL_SetRenderDrawColor(gc.renderer,
            gc.bg.r, gc.bg.g, gc.bg.b, gc.bg.a);
    SDL_RenderClear(gc.renderer);
    SDL_RenderPresent(gc.renderer);
    finished = true;
    return -1;
}

bool Slide::runback(GContext &gc)
{
    finished = false;
    return false;
}

bool Slide::will_clear_screen()
{
    return true;
}

Slide::Slide()
{
    finished = false;
}

bool Slide::explain(vector<string> prms, Instruction *&inst)
{
    if(prms.size()>=1 && prms[0].compare("newpage")==0) {
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
