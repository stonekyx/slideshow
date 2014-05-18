#include "playctl.h"

int main()
{
    Slideshow::PlayControl *ctl =
        new Slideshow::PlayControl("./scriptfile.so", "test.slide");
    delete ctl;
    return 0;
}

