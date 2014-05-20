#ifndef SLIDE_H

#define SLIDE_H

#include <vector>

#include <SDL.h>

#include "instruction.h"

namespace Slideshow {
    class Slide : public Instruction {
        private:
            bool finished;
        protected:
            Slide();
        public:
            int run(GContext &);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
