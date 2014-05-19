#include <iostream>
#include <string>

#include "gcontextchange.h"

using namespace Slideshow;
using namespace std;

int InstGContext::run(SDL_Window *, SDL_Renderer *)
{
    cout<<"Got gcontext change"<<endl;
    return -2;
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
