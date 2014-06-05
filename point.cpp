#include <boost/lexical_cast.hpp>

#include "point.h"

using namespace Slideshow;
using namespace std;

int InstPoint::run(GContext &gc)
{
    int x, y;
    this->get_point(&x, &y);
    if(this->relative) {
        //parse relative coordinates to absolute plain numbers.
        int win_w, win_h;
        SDL_GetWindowSize(gc.window, &win_w, &win_h);
        x += win_w/2;
        y += win_h/2;
        this->relative = false;
    }
    this->x = boost::lexical_cast<string>(x);
    this->y = boost::lexical_cast<string>(y);
    return -2;
}

void InstPoint::get_point(int *x, int *y)
{
    *x = Instruction::parse_coor(this->x);
    *y = Instruction::parse_coor(this->y);
}

bool InstPoint::explain(vector<string> prms, Instruction *&inst)
{
    if(prms.size()<3 || prms[0].compare("point")) {
        return false;
    }
    InstPoint *res = new InstPoint();
    if(prms.size()>=4 && !prms[1].compare("rel")) {
        //relative point
        res->relative = true;
        res->x = prms[2];
        res->y = prms[3];
    } else {
        //absolute point
        res->relative = false;
        res->x = prms[1];
        res->y = prms[2];
    }
    inst = res;
    return true;
}

extern "C"
InstPoint::explain_t get_explain()
{
    return InstPoint::explain;
}
