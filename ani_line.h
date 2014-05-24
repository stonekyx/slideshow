#ifndef ANI_LINE_H

#define ANI_LINE_H

#include <vector>
#include <string>

#include "instruction.h"
#include "gcontext.h"

namespace Slideshow {
    class InstAniLine : public Instruction {
        private:
            Instruction *subinst;
            std::string tx, ty;
            SDL_Rect tarrect;
            bool finished;
            class Bresenham;
        protected:
        public:
            int run(GContext &);
            bool runback(GContext &);
            void get_point(int *, int *);
            void get_size(int *, int *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
