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
            bool runback(GContext &);
            bool will_clear_screen();
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
