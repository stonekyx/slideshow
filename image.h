#ifndef IMAGE_H

#define IMAGE_H

#include <vector>
#include <string>

#include "instruction.h"

namespace Slideshow {
    class InstImg : public Instruction {
        private:
            std::string x, y;
            std::string path;
            bool finished;
        protected:
            InstImg();
        public:
            int run(GContext &);
            void get_point(int *, int *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
