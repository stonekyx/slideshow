#include <iostream>

#include "slide.h"

using namespace Slideshow;
using namespace std;

void Slide::add_inst(Instruction *inst)
{
    this->inst.push_back(inst);
}

void Slide::run()
{
    cout<<"Slide start"<<endl;
    for(vector<Instruction*>::iterator it = inst.begin();
            it!=inst.end(); it++) {
        (*it)->run();
    }
    cout<<"Slide end"<<endl;
}

bool Slide::explain(vector<Parameter*> prms, Instruction *&inst)
{
    if(dynamic_cast<StrParameter*>(prms[0])->get_value().compare("newpage")==0) {
        inst = new Slide();
        return true;
    }
    return false;
}
