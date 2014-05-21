#include <iostream>
#include <cstdlib>
#include <cstring>

#include "playctl.h"

using namespace std;

int main(int argc, char *argv[])
{
    const char *filename=NULL, *screen_size="640x480";
    if(argc<2) {
        cerr<<"Not enough arguments."<<endl;
        return 1;
    } else {
        filename = argv[1];
        if(argc>=3) {
            screen_size = argv[2];
        }
    }
    if(!strstr(screen_size, "x")) {
        cerr<<"Wrong screen size."<<endl;
        return 2;
    }
    Slideshow::PlayControl *ctl =
        new Slideshow::PlayControl("./inst_plugins/scriptfile.so", filename,
                atoi(screen_size), atoi(strstr(screen_size, "x")+1));
    ctl->play();
    delete ctl;
    return 0;
}

