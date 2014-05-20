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
            int x, y;
        protected:
            InstText(int, int, const std::string &text);
        public:
            int run(GContext &);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
