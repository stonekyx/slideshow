#include "playctl.h"

int main()
{
    Slideshow::PlayControl *ctl =
        new Slideshow::PlayControl("./inst_plugins/scriptfile.so", "test.slide");
    ctl->play();
    delete ctl;
    return 0;
}

