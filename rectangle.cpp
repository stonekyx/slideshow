#include <iostream>
#include <string>

#include "rectangle.h"

using namespace Slideshow;
using namespace std;

void InstRect::run()
{
    cout<<"Got rect"<<endl;
}

bool InstRect::explain(vector<Parameter*> prms, Instruction *&inst)
{
    if(dynamic_cast<StrParameter*>(prms[0])->get_value().compare("rect")==0) {
        inst = new InstRect();
        return true;
    }
    return false;
}

extern "C"
InstRect::explain_t get_explain()
{
    return InstRect::explain;
}
