#ifndef RECTANGLE_H

#define RECTANGLE_H

#include "instruction.h"
#include <vector>

namespace Slideshow {
    class InstRect : public Instruction {
        private:
            SDL_Rect rect;
            bool finished;
        protected:
            InstRect();
        public:
            int run(SDL_Window *, SDL_Renderer *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
