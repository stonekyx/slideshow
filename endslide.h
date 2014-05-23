#ifndef ENDSLIDE_H

#define ENDSLIDE_H

#include <vector>

#include "instruction.h"

namespace Slideshow {
    class EndSlide : public Instruction {
        private:
            int delay;
            bool finished;
        protected:
            EndSlide();
        public:
            int run(GContext &);
            bool runback(GContext &);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
