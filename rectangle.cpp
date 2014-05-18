#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "rectangle.h"

using namespace Slideshow;
using namespace std;

void InstRect::run(SDL_Window *)
{
    cout<<"Got rect"<<endl;
    SDL_Delay(1000);
}

bool InstRect::explain(vector<string> prms, Instruction *&inst)
{
    if(prms[0].compare("rect")) {
        return false;
    }
    InstRect *res = new InstRect();
    res->x = boost::lexical_cast<int>(prms[1]);
    res->y = boost::lexical_cast<int>(prms[2]);
    res->w = boost::lexical_cast<int>(prms[3]);
    res->h = boost::lexical_cast<int>(prms[4]);
    inst = res;
    return true;
}

extern "C"
InstRect::explain_t get_explain()
{
    return InstRect::explain;
}
