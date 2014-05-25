#include <iostream>
#include <vector>
#include <exception>
#include <dlfcn.h>

#include <SDL.h>

#include <GL/gl.h>

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

        void init_sdl(int w, int h, bool disable_gl);
        void deinit_sdl();
};

void PlayControl::Private::init_sdl(int w, int h, bool disable_gl)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    gc.has_gl = true;
    Uint32 win_flags;
    if(w>0 && h>0) {
        win_flags = SDL_WINDOW_SHOWN;
    } else {
        win_flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    gc.window = NULL;
    if(!disable_gl) {
        gc.window = SDL_CreateWindow("Slideshow",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                w, h, win_flags | SDL_WINDOW_OPENGL);
    }
    if(gc.window==NULL) {
        gc.window = SDL_CreateWindow("Slideshow",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                w, h, win_flags);
        gc.has_gl = false;
    }
    if(gc.window==NULL) {
        throw new exception();
    }

    gc.renderer = NULL;
    if(!disable_gl) {
        gc.renderer = SDL_CreateRenderer(gc.window, -1,
                SDL_RENDERER_ACCELERATED
                | SDL_RENDERER_TARGETTEXTURE
                | SDL_RENDERER_PRESENTVSYNC
                );
    }
    if(gc.renderer==NULL) {
        gc.renderer = SDL_CreateRenderer(gc.window, -1,
                SDL_RENDERER_TARGETTEXTURE
                );
        gc.has_gl = false;
    }
    if(gc.renderer==NULL) {
        throw new exception();
    }

    if(!gc.has_gl) {
        cerr<<"OpenGL disabled."<<endl;
    }

    SDL_Delay(100); //seems awesome wm needs this.
    gc.fg.a = 255; gc.fg.r = gc.fg.g = gc.fg.b = 0;
    gc.bg.a = 255; gc.bg.r = gc.bg.g = gc.bg.b = 255;
    SDL_SetRenderDrawColor(gc.renderer,
            gc.bg.r, gc.bg.g, gc.bg.b, gc.bg.a);
    SDL_RenderClear(gc.renderer);
    SDL_RenderPresent(gc.renderer);

    /*gc.has_gl = false;
    if(gc.has_gl) {
        cout<<"Using OpenGL"<<endl;
        gc.glcontext = SDL_GL_CreateContext(gc.window);
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(gc.window);
    }*/
}

void PlayControl::Private::deinit_sdl()
{
    /*if(gc.has_gl) {
        SDL_GL_DeleteContext(gc.glcontext);
    }*/
    SDL_DestroyRenderer(gc.renderer);
    SDL_DestroyWindow(gc.window);
    SDL_Quit();
}

//---------------------------------------------------

PlayControl::PlayControl(const char *file_plugin, const char *file, int w, int h, bool disable_gl) :
    priv(new Private())
{
    void *handle = dlopen(file_plugin, RTLD_LAZY | RTLD_GLOBAL);
    file_creator_t creator = (file_creator_t)dlsym(handle, "create_file_obj");
    priv->file_destroyer = (file_destroyer_t)dlsym(handle, "destroy_file_obj");
    priv->file = creator(file);

    priv->init_sdl(w, h, disable_gl);
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
        SDL_Keycode kc;
        if(delay<0) { //instruction delay
            kc = wait_key(SDLK_UNKNOWN);
        } else {
            kc = wait_key_timeout(delay);
        }
        if(kc==SDLK_q) {
            return;
        } else if(kc==SDLK_UP || kc==SDLK_LEFT) {
            while(kc==SDLK_UP || kc==SDLK_LEFT) {
                if(!priv->file->runback(priv->gc)) {
                    break;
                }
                kc = wait_key(SDLK_UNKNOWN);
            }
        }
    }
}
