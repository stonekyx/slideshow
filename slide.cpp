#include <iostream>

#include "slide.h"

using namespace Slideshow;
using namespace std;

void Slide::add_inst(Instruction *inst)
{
    this->inst.push_back(inst);
}

void Slide::run(SDL_Window *window)
{
    cout<<"Slide start"<<endl;
    for(vector<Instruction*>::iterator it = inst.begin();
            it!=inst.end(); it++) {
        (*it)->run(window);
    }
    cout<<"Slide end"<<endl;
    SDL_Delay(1000);
}

bool Slide::explain(vector<Parameter*> prms, Instruction *&inst)
{
    if(dynamic_cast<StrParameter*>(prms[0])->get_value().compare("newpage")==0) {
        inst = new Slide();
        return true;
    }
    return false;
}
