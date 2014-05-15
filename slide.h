#ifndef SLIDE_H

#define SLIDE_H

#include <vector>

#include "instruction.h"

namespace Slideshow {
    class Slide : public Instruction {
        private:
            std::vector<Instruction*> inst;
        protected:
        public:
            void run();
            void add_inst(Instruction *);
            static bool explain(std::vector<Parameter*>, Instruction *&);
    };
}

#endif