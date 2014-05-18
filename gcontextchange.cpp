#include <iostream>
#include <string>

#include "gcontextchange.h"

using namespace Slideshow;
using namespace std;

void InstGContext::run(SDL_Window *)
{
    cout<<"Got gcontext change"<<endl;
    SDL_Delay(1000);
}

bool InstGContext::explain(vector<string> prms, Instruction *&inst)
{
    if(prms[0].compare("font")==0) {
        inst = new InstGContext();
        return true;
    } else if(prms[0].compare("fontsize")==0) {
        inst = new InstGContext();
        return true;
    } else if(prms[0].compare("color")==0) {
        inst = new InstGContext();
        return true;
    }
    return false;
}

extern "C"
InstGContext::explain_t get_explain()
{
    return InstGContext::explain;
}
