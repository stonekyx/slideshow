#ifndef RECTANGLE_H

#define RECTANGLE_H

#include "instruction.h"
#include <vector>

namespace Slideshow {
    class InstRect : public Instruction {
        private:
        protected:
        public:
            void run();
            static bool explain(std::vector<Parameter*>, Instruction *&);
    };
}

#endif
