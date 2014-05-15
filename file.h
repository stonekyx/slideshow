#ifndef FILE_H

#define FILE_H

#include <vector>

#include "slide.h"
#include "instruction.h"

namespace Slideshow {
    class File {
        private:
        protected:
            File() {}
        public:
            virtual ~File() {};
            virtual bool getSlides(std::vector<Slide*> &)=0;
    };
    typedef File *(*file_creator_t)(const char *);
    typedef void (*file_destroyer_t)(File *);
}

#endif
