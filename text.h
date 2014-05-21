#ifndef TEXT_H

#define TEXT_H

#include <vector>
#include <string>

#include "instruction.h"

namespace Slideshow {
    class InstText : public Instruction {
        private:
            bool finished;
            std::string text;
            std::string x, y;
        protected:
            InstText();
        public:
            int run(GContext &);
            void get_point(int *, int *);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
