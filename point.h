#ifndef POINT_H

#define POINT_H

#include <vector>
#include <string>

#include "instruction.h"
#include "gcontext.h"

namespace Slideshow {
    class InstPoint : public Instruction {
        private:
            std::string x, y;
            bool relative;
        protected:
        public:
            int run(GContext &);
            void get_point(int *, int *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
