#ifndef MTEXT_H

#define MTEXT_H

#include <vector>
#include <string>

#include "instruction.h"
#include "gcontext.h"

namespace Slideshow {
    class InstMText : public Instruction {
        private:
            class Segment {
                public:
                    std::string font, text;
                    int font_size;
                    bool lb;
                    bool pause;
            };
            std::vector<Segment> segments;
            std::vector<Segment>::iterator it;
            int cx, cy, line_height;
            std::string x, y;
            int w, h;
            bool finished;
            void calc_size(GContext &);
        protected:
            InstMText();
        public:
            int run(GContext &);
            bool runback(GContext &);
            void get_point(int *, int *);
            void get_size(int *, int *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
