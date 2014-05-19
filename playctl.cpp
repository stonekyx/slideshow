#include <iostream>
#include <vector>
#include <exception>
#include <dlfcn.h>

#include <SDL.h>

#include "file.h"
#include "slide.h"
#include "util.h"
#include "playctl.h"

using namespace Slideshow;
using namespace std;

class PlayControl::Private {
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;
        file_destroyer_t file_destroyer;
        File *file;

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
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
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
    while((delay = priv->file->run(priv->window, priv->renderer))!=-2) {
        if(delay<0) { //instruction delay
            wait_key(SDLK_UNKNOWN);
        } else {
            SDL_Delay(delay);
        }
    }
}
