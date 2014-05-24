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

bool InstAniLine::Bresenham::hasnext()
{
    if((dx>dy && i<=dx) || (dx<=dy && i<=dy)) {
        return true;
    }
    return false;
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
    SDL_Texture *orig_target = SDL_GetRenderTarget(gc.renderer);
    if(SDL_SetRenderTarget(gc.renderer, subinst_texture)) {
        throw new exception();
    }
    while(subinst->run(gc)!=-2) {
    }
    if(SDL_SetRenderTarget(gc.renderer, NULL)) {
        throw new exception();
    }

    SDL_Texture *win_texture =
        SDL_CreateTexture(gc.renderer,
                SDL_GetWindowPixelFormat(gc.window),
                SDL_TEXTUREACCESS_STREAMING,
                win_w, win_h);
    void *win_pixels;
    int win_pitch;
    SDL_LockTexture(win_texture, NULL, &win_pixels, &win_pitch);
    SDL_Surface *win_surface = SDL_GetWindowSurface(gc.window);
    if(win_surface==NULL) {
        SDL_GL_SwapWindow(gc.window);
        glReadPixels(0, 0, win_w, win_h, GL_RGBA, GL_UNSIGNED_BYTE, win_pixels);
        unsigned char *wp =
            (unsigned char*)win_pixels; //just alias
        unsigned char *swap = new unsigned char[win_w*4];
        for(int i=0; i<win_h/2; i++) {
            memmove(swap, wp+i*win_w*4, win_w*4);
            memmove(wp+i*win_w*4, wp+(win_h-i-1)*win_w*4,
                    win_w*4);
            memmove(wp+(win_h-i-1)*win_w*4, swap, win_w*4);
        }
        delete[] swap;
    } else {
        memcpy(win_pixels, win_surface->pixels,
                win_surface->pitch*win_surface->h);
    }
    SDL_UnlockTexture(win_texture);
    win_pixels = NULL;

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
    SDL_SetTextureBlendMode(win_texture, SDL_BLENDMODE_BLEND);
    for(Bresenham b(tarrect.x, tarrect.y, tx, ty);
            b.next(&tarrect.x, &tarrect.y) &&
            b.next(&tarrect.x, &tarrect.y) &&
            b.next(&tarrect.x, &tarrect.y); ) {
        SDL_RenderCopy(gc.renderer, subinst_texture,
                &subrect, &tarrect);
        SDL_RenderPresent(gc.renderer);
        SDL_Delay(10);
        SDL_RenderCopy(gc.renderer, win_texture, &tarrect, &tarrect);
    }
    if(SDL_SetRenderTarget(gc.renderer, orig_target)) {
        throw new exception();
    }
    SDL_RenderCopy(gc.renderer, subinst_texture, &subrect, &tarrect);
    SDL_RenderPresent(gc.renderer);

    SDL_DestroyTexture(subinst_texture);
    SDL_DestroyTexture(win_texture);
    finished = true;
    return -1;
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
