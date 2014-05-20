#ifndef GCONTEXT_CHANGE_H

#define GCONTEXT_CHANGE_H

#include <vector>
#include <string>

#include <SDL.h>

#include "instruction.h"

namespace Slideshow {
    class InstGContext : public Instruction {
        private:
        protected:
        public:
            virtual int run(GContext &) = 0;
            static bool explain(std::vector<std::string>, Instruction *&);
    };
    class InstGContextFG : public InstGContext {
        private:
            SDL_Color color;
        public:
            InstGContextFG(int r, int g, int b, int a) {
                color.r = r; color.g = g; color.b = b;
                color.a = a;
            }
            int run(GContext &);
    };
    class InstGContextBG : public InstGContext {
        private:
            SDL_Color color;
        public:
            InstGContextBG(int r, int g, int b, int a) {
                color.r = r; color.g = g; color.b = b;
                color.a = a;
            }
            int run(GContext &);
    };
    class InstGContextFontFamily : public InstGContext {
        private:
            std::string font_family;
        public:
            InstGContextFontFamily(const std::string &ff) :
                font_family(ff) {}
            int run(GContext &);
    };
    class InstGContextFontSize : public InstGContext {
        private:
            int font_size;
        public:
            InstGContextFontSize(int fs) : font_size(fs) {}
            int run(GContext &);
    };
}

#endif
