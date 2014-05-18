#include <iostream>

#include "image.h"

using namespace Slideshow;
using namespace std;

void InstImg::run(SDL_Window *)
{
    cout<<"Got image"<<endl;
    SDL_Delay(1000);
}

bool InstImg::explain(vector<string> prms, Instruction *&inst)
{
    if(prms[0].compare("img")==0) {
        inst = new InstImg();
        return true;
    }
    return false;
}

extern "C"
InstImg::explain_t get_explain()
{
    return InstImg::explain;
}
