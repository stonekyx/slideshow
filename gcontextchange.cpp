#include <iostream>
#include <string>

#include "gcontextchange.h"

using namespace Slideshow;
using namespace std;

void InstGContext::run()
{
    cout<<"Got gcontext change"<<endl;
}

bool InstGContext::explain(vector<Parameter*> prms, Instruction *&inst)
{
    const string &str = dynamic_cast<StrParameter*>(prms[0])->get_value();
    if(str.compare("font")==0) {
        inst = new InstGContext();
        return true;
    } else if(str.compare("fontsize")==0) {
        inst = new InstGContext();
        return true;
    } else if(str.compare("color")==0) {
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
