#ifndef IMAGE_H

#define IMAGE_H

#include <vector>

#include "instruction.h"
#include "parameter.h"

namespace Slideshow {
    class InstImg : public Instruction {
        private:
        protected:
        public:
            void run();
            static bool explain(std::vector<Parameter*>, Instruction *&);
    };
}

#endif
