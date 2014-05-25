#include <boost/lexical_cast.hpp>

#include <SDL_ttf.h>

#include "util.h"
#include "mtext.h"

using namespace Slideshow;
using namespace std;

int InstMText::run(GContext &gc)
{
    if(this->finished) {
        this->finished = false;
        return -2;
    }
    int line_width=0;
    int width=0, height=0;
    int line_height=0;
    //new line is forced at the end.
    for(vector<Segment>::iterator it = segments.begin();
            it!=segments.end(); it++) {
        if(it->lb) {
            if(width<line_width) {
                width = line_width;
            }
            line_width=0;
            height+=line_height;
            line_height=0;
            continue;
        }
        if(it->font_size==-1) {
            it->font_size = gc.font_size;
        }
        if(it->font.length()==0) {
            it->font = gc.font_family;
        }
        TTF_Font *font = TTF_OpenFont(it->font.c_str(), it->font_size);
        int textw, texth;
        TTF_SizeUTF8(font, it->text.c_str(), &textw, &texth);
        if(line_height<texth) {
            line_height = texth;
        }
        line_width += textw;
    }
    this->w = width;
    this->h = height;
    int cx, cy, origx;
    this->get_point(&cx, &cy);
    origx = cx;
    this->x = boost::lexical_cast<string>(cx);
    this->y = boost::lexical_cast<string>(cy);
    line_height = 0;
    for(vector<Segment>::iterator it = segments.begin();
            it!=segments.end(); it++) {
        if(it->lb) {
            cx = origx;
            cy += line_height;
            continue;
        }
        TTF_Font *font = TTF_OpenFont(it->font.c_str(), it->font_size);
        SDL_Surface *text_sur = TTF_RenderUTF8_Shaded(font, it->text.c_str(), gc.fg, gc.bg);
        SDL_SetColorKey(text_sur, SDL_TRUE, SDL_MapRGB(text_sur->format, 255, 255, 255));
        SDL_Texture *text_texture = SDL_CreateTextureFromSurface(gc.renderer, text_sur);
        SDL_Rect rect = get_rect_from_pos(cx, cy, text_texture);
        SDL_SetTextureBlendMode(text_texture, SDL_BLENDMODE_NONE);
        SDL_RenderCopy(gc.renderer, text_texture, NULL, &rect);
        SDL_DestroyTexture(text_texture);
        SDL_FreeSurface(text_sur);
        TTF_CloseFont(font);
        cx+=rect.w;
        if(line_height<rect.h) {
            line_height = rect.h;
        }
    }
    SDL_RenderPresent(gc.renderer);
    this->finished = true;
    return this->delay;
}

bool InstMText::runback(GContext &gc)
{
    finished = false;
    return false;
}

void InstMText::get_point(int *x, int *y)
{
    *x = this->parse_coor(this->x);
    *y = this->parse_coor(this->y);
}

void InstMText::get_size(int *w, int *h)
{
    *w = this->w;
    *h = this->h;
}

InstMText::InstMText()
{
}

bool InstMText::explain(vector<string> prms, Instruction *&inst)
{
    if(prms.size()<3 || prms[0].compare("mtext")) {
        return false;
    }
    InstMText *res = new InstMText();
    res->finished = false;
    res->x = prms[1];
    res->y = prms[2];
    prms.push_back("lb"); //force new line
    for(vector<string>::iterator it = prms.begin()+3;
            it!=prms.end(); ) {
        Segment seg;
        if(it->compare("lb")==0) {
            seg.lb = true;
            it++;
        } else if(it+1!=prms.end()) {
            seg.lb = false;
            seg.font = *it++;
            seg.font_size = -1;
            unsigned int sep;
            if((sep=seg.font.find(":"))!=seg.font.npos) {
                seg.font_size = boost::lexical_cast<int>(seg.font.substr(sep+1));
                seg.font = seg.font.substr(0, sep);
            }
            if(seg.font.length()>0) {
                get_full_fontpath(seg.font);
            }
            seg.text = *it++;
        } else {
            continue;
        }
        res->segments.push_back(seg);
    }
    inst = res;
    return true;
}

extern "C"
InstMText::explain_t get_explain()
{
    return InstMText::explain;
}
