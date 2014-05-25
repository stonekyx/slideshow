#include <iostream>
#include <exception>
#include <cstdlib>

#include <boost/lexical_cast.hpp>

#include <GL/gl.h>

#include "ani_line.h"

using namespace Slideshow;
using namespace std;

class InstAniLine::Bresenham {
    private:
        int a, b, delta, x, y, dx, dy, stepx, stepy, i;
        int retx, rety;
    public:
        Bresenham(int x1, int y1, int x2, int y2);
        bool next(int *, int *);
        bool next(int times, int *, int *);
        bool hasnext();
};

InstAniLine::Bresenham::Bresenham(int x1, int y1, int x2, int y2)
{
    this->dx = labs(x1 - x2);
    this->dy = labs(y1 - y2);

    if(x2 > x1) {
        this->stepx = 1;
    } else {
        this->stepx = -1;
    }

    if(y2 > y1) {
        this->stepy = 1;
    } else {
        this->stepy = -1;
    }

    this->x = x1;
    this->y = y1;

    /* -1 < 斜率 < +1 */
    if(this->dx > this->dy) {
        this->a = this->dy << 1;
        this->b = (this->dy - this->dx) << 1;
        this->delta = (this->dy << 1) - this->dx;
        this->i = 0;
    } else {/* 斜率 <= -1 或者 +1 <= 斜率 */
        this->a = this->dx << 1;
        this->b = (this->dx - this->dy) << 1;
        this->delta = (this->dx << 1) - this->dy;
        this->i = 0;
    }
}

bool InstAniLine::Bresenham::next(int *x, int *y)
{
    /* -1 < 斜率 < +1 */
    if(this->dx > this->dy) {
        if(this->i <= this->dx) {
            this->retx = this->x;
            this->rety = this->y;

            this->x += this->stepx;
            if(this->delta < 0) {
                this->delta += this->a;
            } else {
                this->delta += this->b;
                this->y += this->stepy;
            }

            this->i ++; /* simulate a one-time for loop. */
            *x = this->retx;
            *y = this->rety;
            return true;
        }
    } else {
        if(this->i <= this->dy) {
            this->retx = this->x;
            this->rety = this->y;

            this->y += this->stepy;
            if(this->delta < 0) {
                this->delta += this->a;
            } else {
                this->delta += this->b;
                this->x += this->stepx;
            }

            this->i ++;
            *x = this->retx;
            *y = this->rety;
            return true;
        }
    }
    return false;
}

bool InstAniLine::Bresenham::next(int times, int *x, int *y)
{
    while(times && this->next(x,y)) {
        times--;
    }
    if(times) return false;
    return true;
}

bool InstAniLine::Bresenham::hasnext()
{
    if((dx>dy && i<=dx) || (dx<=dy && i<=dy)) {
        return true;
    }
    return false;
}

SDL_Texture *InstAniLine::create_window_snapshot(GContext &gc)
{
    void *pixels;
    int pitch;
    int win_w, win_h;
    SDL_GetWindowSize(gc.window, &win_w, &win_h);

    SDL_Texture *win_texture =
        SDL_CreateTexture(gc.renderer,
                SDL_GetWindowPixelFormat(gc.window),
                SDL_TEXTUREACCESS_STREAMING,
                win_w, win_h);
    if(SDL_LockTexture(win_texture, NULL, &pixels, &pitch)) {
        cerr<<SDL_GetError()<<endl;
        throw new exception();
    }
    SDL_Surface *win_surface = SDL_GetWindowSurface(gc.window);
    if(win_surface==NULL) {
        SDL_GL_SwapWindow(gc.window);
        glReadPixels(0, 0, win_w, win_h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        unsigned char *wp =
            (unsigned char*)pixels; //just alias
        unsigned char *swap = new unsigned char[pitch];
        for(int i=0; i<win_h/2; i++) {
            memmove(swap, wp+i*pitch, pitch);
            memmove(wp+i*pitch, wp+(win_h-i-1)*pitch,
                    pitch);
            memmove(wp+(win_h-i-1)*pitch, swap, pitch);
        }
        delete[] swap;
    } else {
        memcpy(pixels, win_surface->pixels,
                win_surface->pitch*win_surface->h);
    }
    SDL_UnlockTexture(win_texture);
    pixels = NULL;
    return win_texture;
}

//---------------public interface---------------------

int InstAniLine::run(GContext &gc)
{
    if(finished) {
        finished = false;
        return -2;
    }
    int win_w, win_h;
    SDL_GetWindowSize(gc.window, &win_w, &win_h);

    SDL_Texture *subinst_texture =
        SDL_CreateTexture(gc.renderer,
                SDL_GetWindowPixelFormat(gc.window),
                SDL_TEXTUREACCESS_TARGET,
                win_w, win_h);
    if(subinst_texture==NULL) {
        cerr<<SDL_GetError()<<endl;
        throw new exception();
    }

    SDL_Texture *orig_target = SDL_GetRenderTarget(gc.renderer);
    if(SDL_SetRenderTarget(gc.renderer, subinst_texture)) {
        throw new exception();
    }
    while(subinst->run(gc)!=-2) {
    }
    if(SDL_SetRenderTarget(gc.renderer, NULL)) {
        throw new exception();
    }

    SDL_Texture *win_texture = create_window_snapshot(gc);

    SDL_Rect subrect;
    subinst->get_point(&subrect.x, &subrect.y);
    subinst->get_size(&subrect.w, &subrect.h);
    tarrect = subrect;

    int tx, ty;
    tx = this->parse_coor(this->tx);
    ty = this->parse_coor(this->ty);
    this->tx = boost::lexical_cast<string>(tx);
    this->ty = boost::lexical_cast<string>(ty);

    SDL_SetRenderDrawColor(gc.renderer,
            gc.bg.r, gc.bg.g, gc.bg.b, gc.bg.a);
    SDL_SetTextureBlendMode(subinst_texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(win_texture, SDL_BLENDMODE_NONE);
    for(Bresenham b(tarrect.x, tarrect.y, tx, ty);
            b.next(3, &tarrect.x, &tarrect.y); ) {
        SDL_RenderCopy(gc.renderer, subinst_texture,
                &subrect, &tarrect);
        SDL_RenderPresent(gc.renderer);
        //SDL_Delay(10);
        SDL_RenderCopy(gc.renderer, win_texture, &tarrect, &tarrect);
    }
    //last render, onto original target.
    if(SDL_SetRenderTarget(gc.renderer, orig_target)) {
        throw new exception();
    }
    SDL_SetTextureBlendMode(subinst_texture, SDL_BLENDMODE_NONE);
    SDL_RenderCopy(gc.renderer, subinst_texture, &subrect, &tarrect);
    if(orig_target==NULL) {
        SDL_RenderPresent(gc.renderer);
    }

    SDL_DestroyTexture(subinst_texture);
    SDL_DestroyTexture(win_texture);
    finished = true;
    return this->delay;
}

bool InstAniLine::runback(GContext &)
{
    finished = false;
    return false;
}

void InstAniLine::get_point(int *x, int *y)
{
    *x = tarrect.x;
    *y = tarrect.y;
}

void InstAniLine::get_size(int *w, int *h)
{
    *w = tarrect.w;
    *h = tarrect.h;
}

bool InstAniLine::explain(vector<string> prms, Instruction *&inst)
{
    if(prms.size()<3 || prms[0].compare("aniline")) {
        return false;
    }
    InstAniLine *res = new InstAniLine();
    res->tx = prms[1];
    res->ty = prms[2];
    res->finished = false;
    vector<string> subprms(prms.begin()+3, prms.end());
    if(!Instruction::explain(subprms, res->subinst)) {
        delete res;
        return false;
    }
    inst = res;
    return true;
}

extern "C"
InstAniLine::explain_t get_explain()
{
    return InstAniLine::explain;
}
