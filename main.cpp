#include "playctl.h"

int main()
{
    Slideshow::PlayControl *ctl =
        new Slideshow::PlayControl("./scriptfile.so", "test.slide");
    ctl->play();
    delete ctl;
    return 0;
}

