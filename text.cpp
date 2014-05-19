#include <iostream>

#include "text.h"

using namespace Slideshow;
using namespace std;

int InstText::run(SDL_Window *, SDL_Renderer *)
{
    if(finished) {
        finished = false;
        return -2;
    }
    cout<<"Got text"<<endl;
    finished = true;
    return -1;
}

InstText::InstText()
{
    finished = false;
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
