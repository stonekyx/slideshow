#ifndef TEXT_H

#define TEXT_H

#include <vector>

#include "instruction.h"

namespace Slideshow {
    class InstText : public Instruction {
        private:
            bool finished;
        protected:
            InstText();
        public:
            int run(SDL_Window *, SDL_Renderer *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
