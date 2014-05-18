#ifndef TEXT_H

#define TEXT_H

#include <vector>

#include "instruction.h"
#include "parameter.h"

namespace Slideshow {
    class InstText : public Instruction {
        private:
        protected:
        public:
            void run(SDL_Window *);
            static bool explain(std::vector<Parameter*>, Instruction *&);
    };
}

#endif
