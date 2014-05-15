#include <dlfcn.h>
#include <iostream>
#include <vector>

#include "file.h"
#include "slide.h"

using namespace std;

int main()
{
    void *handle = dlopen("./scriptfile.so", RTLD_LAZY);
    Slideshow::file_creator_t creator = (Slideshow::file_creator_t)dlsym(handle, "create_file_obj");
    Slideshow::file_destroyer_t destroyer = (Slideshow::file_destroyer_t)dlsym(handle, "destroy_file_obj");
    Slideshow::File *file = creator("test.slide");
    vector<Slideshow::Slide*> res;
    if(file->getSlides(res)) {
        for(vector<Slideshow::Slide*>::iterator it = res.begin();
                it!=res.end(); it++) {
            (*it)->run();
        }
    }
    destroyer(file);
    return 0;
}

