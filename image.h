#ifndef IMAGE_H

#define IMAGE_H

#include <vector>

#include "instruction.h"

namespace Slideshow {
    class InstImg : public Instruction {
        private:
        protected:
        public:
            void run(SDL_Window *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
