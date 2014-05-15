#include <iostream>

#include "image.h"

using namespace Slideshow;
using namespace std;

void InstImg::run()
{
    cout<<"Got image"<<endl;
}

bool InstImg::explain(vector<Parameter*> prms, Instruction *&inst)
{
    if(dynamic_cast<StrParameter*>(prms[0])->get_value().compare("img")==0) {
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
