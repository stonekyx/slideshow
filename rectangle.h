#ifndef RECTANGLE_H

#define RECTANGLE_H

#include "instruction.h"
#include <vector>

namespace Slideshow {
    class InstRect : public Instruction {
        private:
            int x, y, w, h;
        protected:
        public:
            void run(SDL_Window *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
