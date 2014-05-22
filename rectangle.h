#ifndef RECTANGLE_H

#define RECTANGLE_H

#include <vector>
#include <string>

#include "instruction.h"

namespace Slideshow {
    class InstRect : public Instruction {
        private:
            std::string x, y, w, h;
            bool finished;
        protected:
            InstRect();
        public:
            int run(GContext &);
            void get_point(int *, int *);
            void get_size(int *, int *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
