#ifndef SCRIPTFILE_IMPL
# error "Never use \"scriptfile.h\" directly; load scriptfile.so instead."
#endif

#ifndef SCRIPTFILE_H

#define SCRIPTFILE_H

#include <vector>
#include <fstream>

#include "file.h"
#include "slide.h"
#include "parameter.h"

namespace Slideshow {
    class ScriptFile : public File {
        private:
            std::ifstream _file;
            bool read_line(std::vector<Parameter*> &);
        protected:
        public:
            ScriptFile(const char *);
            ~ScriptFile();
            bool getSlides(std::vector<Slide*> &);
    };
}

#endif
