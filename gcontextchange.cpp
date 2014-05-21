#include <iostream>
#include <string>
#include <cstdlib>

#include <boost/lexical_cast.hpp>

#include "gcontextchange.h"

using namespace Slideshow;
using namespace std;

int InstGContextFG::run(GContext &gc)
{
    gc.fg = this->color;
    return -2;
}

int InstGContextBG::run(GContext &gc)
{
    gc.bg = this->color;
    return -2;
}

int InstGContextFontSize::run(GContext &gc)
{
    gc.font_size = this->font_size;
    return -2;
}

int InstGContextFontFamily::run(GContext &gc)
{
    gc.font_family = this->font_family;
    while(gc.font_family.find('/')==gc.font_family.npos) {
        const char *fontdir = getenv("FONTDIR");
        if(fontdir) {
            string dir(fontdir);
            dir+="/";
            dir+=gc.font_family;
            gc.font_family = dir;
            break;
        }
        const char *home = getenv("HOME");
        if(home) {
            string dir(home);
            dir+="/.fonts/";
            dir+=gc.font_family;
            gc.font_family = dir;
            break;
        }
    }
    return -2;
}

bool InstGContext::explain(vector<string> prms, Instruction *&inst)
{
    if(prms.size()>=2 && prms[0].compare("font")==0) {
        inst = new InstGContextFontFamily(prms[1]);
        return true;
    } else if(prms.size()>=2 && prms[0].compare("fontsize")==0) {
        inst = new InstGContextFontSize(boost::lexical_cast<int>(prms[1]));
        return true;
    } else if(prms.size()>=5 && prms[0].compare("fg")==0) {
        inst = new InstGContextFG(
                boost::lexical_cast<int>(prms[1]),
                boost::lexical_cast<int>(prms[2]),
                boost::lexical_cast<int>(prms[3]),
                boost::lexical_cast<int>(prms[4]));
        return true;
    } else if(prms.size()>=5 && prms[0].compare("bg")==0) {
        inst = new InstGContextBG(
                boost::lexical_cast<int>(prms[1]),
                boost::lexical_cast<int>(prms[2]),
                boost::lexical_cast<int>(prms[3]),
                boost::lexical_cast<int>(prms[4]));
        return true;
    }
    return false;
}

extern "C"
InstGContext::explain_t get_explain()
{
    return InstGContext::explain;
}
