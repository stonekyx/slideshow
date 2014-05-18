#ifndef IMAGE_H

#define IMAGE_H

#include <vector>
#include <string>

#include "instruction.h"

namespace Slideshow {
    class InstImg : public Instruction {
        private:
            int x, y;
            std::string path;
        protected:
        public:
            void run(SDL_Window *, SDL_Renderer *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
