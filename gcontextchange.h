#ifndef GCONTEXT_CHANGE_H

#define GCONTEXT_CHANGE_H

#include <vector>

#include "instruction.h"
#include "parameter.h"

namespace Slideshow {
    class InstGContext : public Instruction {
        private:
        protected:
        public:
            void run(SDL_Window *);
            static bool explain(std::vector<Parameter*>, Instruction *&);
    };
}

#endif
