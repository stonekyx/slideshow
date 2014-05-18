#ifndef GCONTEXT_CHANGE_H

#define GCONTEXT_CHANGE_H

#include <vector>

#include "instruction.h"

namespace Slideshow {
    class InstGContext : public Instruction {
        private:
        protected:
        public:
            void run(SDL_Window *, SDL_Renderer *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
