#include <boost/lexical_cast.hpp>

#include "endslide.h"

using namespace Slideshow;
using namespace std;

int EndSlide::run(GContext &gc)
{
    if(!finished) {
        return delay;
    } else {
        finished = false; //for next play
        return -2;
    }
}

bool EndSlide::runback(GContext &gc)
{
    finished = false;
    return false;
}

EndSlide::EndSlide()
{
    finished = false;
}

bool EndSlide::explain(vector<string> prms, Instruction *&inst)
{
    if(prms.size()<1 || prms[0].compare("endpage")) {
        return false;
    }
    EndSlide *res = new EndSlide();
    if(prms.size()>1) {
        res->delay = boost::lexical_cast<int>(prms[1]);
    } else {
        res->delay = -1; //default to wait infinitely
    }
    inst = res;
    return true;
}

extern "C"
EndSlide::explain_t get_explain()
{
    return EndSlide::explain;
}
