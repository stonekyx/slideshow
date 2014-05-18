#include <iostream>
#include <vector>
#include <exception>
#include <dlfcn.h>

#include <SDL2/SDL.h>

#include "file.h"
#include "slide.h"
#include "playctl.h"

using namespace Slideshow;
using namespace std;

class PlayControl::Private {
    public:
        vector<Slide*> slides;
        SDL_Window *window;

        void init_sdl();
        void deinit_sdl();
};

void PlayControl::Private::init_sdl()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Slideshow",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_SHOWN);
    if(window==NULL) {
        cerr<<"Failed creating SDL window"<<endl;
        throw new exception();
    } else {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect rect;
        rect.x = rect.y = 100;
        rect.w = rect.h = 200;
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(2000);
    }
}

void PlayControl::Private::deinit_sdl()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//---------------------------------------------------

PlayControl::PlayControl(const char *file_plugin, const char *file) :
    priv(new Private())
{
    void *handle = dlopen(file_plugin, RTLD_LAZY);
    file_creator_t creator = (file_creator_t)dlsym(handle, "create_file_obj");
    file_destroyer_t destroyer = (file_destroyer_t)dlsym(handle, "destroy_file_obj");
    File *f = creator(file);
    if(!f->getSlides(priv->slides)) {
        throw new exception();
    }
    destroyer(f);

    priv->init_sdl();
}

PlayControl::~PlayControl()
{
    priv->deinit_sdl();

    for(vector<Slide*>::iterator it = priv->slides.begin();
            it!=priv->slides.end(); it++) {
        delete (*it);
    }
}
