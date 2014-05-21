#ifndef GCONTEXT_H

#define GCONTEXT_H

#include <string>

#include <SDL.h>

namespace Slideshow {
    class GContext {
        private:
        protected:
        public:
            GContext() {
                window = NULL;
                renderer = NULL;
                font_size = 0;
            }
            SDL_Color fg, bg;
            std::string font_family;
            int font_size;
            SDL_Window *window;
            SDL_Renderer *renderer;
    };
}

#endif
