#include <iostream>

#include "text.h"

using namespace Slideshow;
using namespace std;

void InstText::run(SDL_Window *, SDL_Renderer *)
{
    cout<<"Got text"<<endl;
    SDL_Delay(1000);
}

bool InstText::explain(vector<string> prms, Instruction *&inst)
{
    if(prms[0].compare("text")==0) {
        inst = new InstText();
        return true;
    }
    return false;
}

extern "C"
InstText::explain_t get_explain()
{
    return InstText::explain;
}
