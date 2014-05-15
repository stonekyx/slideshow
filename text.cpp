#include <iostream>

#include "text.h"

using namespace Slideshow;
using namespace std;

void InstText::run()
{
    cout<<"Got text"<<endl;
}

bool InstText::explain(vector<Parameter*> prms, Instruction *&inst)
{
    if(dynamic_cast<StrParameter*>(prms[0])->get_value().compare("text")==0) {
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
