#include <iostream>
#include <vector>
#include <exception>
#include <dlfcn.h>

#include <SDL.h>

#include "file.h"
#include "util.h"
#include "gcontext.h"
#include "playctl.h"

using namespace Slideshow;
using namespace std;

class PlayControl::Private {
    public:
        file_destroyer_t file_destroyer;
        File *file;
        GContext gc;

        void init_sdl();
        void deinit_sdl();
};

void PlayControl::Private::init_sdl()
{
    SDL_Init(SDL_INIT_VIDEO);
    gc.window = SDL_CreateWindow("Slideshow",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_SHOWN);
    if(gc.window==NULL) {
        cerr<<"Failed creating SDL window"<<endl;
        throw new exception();
    }
    gc.renderer = SDL_CreateRenderer(gc.window, -1, 0);
    gc.fg.a = 255; gc.fg.r = gc.fg.g = gc.fg.b = 0;
    gc.bg.a = 255; gc.bg.r = gc.bg.g = gc.bg.b = 255;
    SDL_SetRenderDrawColor(gc.renderer,
            gc.bg.r, gc.bg.g, gc.bg.b, gc.bg.a);
    SDL_RenderClear(gc.renderer);
    SDL_RenderPresent(gc.renderer);
}

void PlayControl::Private::deinit_sdl()
{
    SDL_DestroyRenderer(gc.renderer);
    SDL_DestroyWindow(gc.window);
    SDL_Quit();
}

//---------------------------------------------------

PlayControl::PlayControl(const char *file_plugin, const char *file) :
    priv(new Private())
{
    void *handle = dlopen(file_plugin, RTLD_LAZY);
    file_creator_t creator = (file_creator_t)dlsym(handle, "create_file_obj");
    priv->file_destroyer = (file_destroyer_t)dlsym(handle, "destroy_file_obj");
    priv->file = creator(file);

    priv->init_sdl();
}

PlayControl::~PlayControl()
{
    priv->deinit_sdl();

    priv->file_destroyer(priv->file);

    delete priv;
}

void PlayControl::play()
{
    int delay;
    while((delay = priv->file->run(priv->gc))!=-2) {
        if(delay<0) { //instruction delay
            wait_key(SDLK_UNKNOWN);
        } else {
            SDL_Delay(delay);
        }
    }
}
