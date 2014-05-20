#ifndef SCRIPTFILE_IMPL
# error "Never use \"scriptfile.h\" directly; load scriptfile.so instead."
#endif

#ifndef SCRIPTFILE_H

#define SCRIPTFILE_H

#include <vector>
#include <string>
#include <fstream>

#include "file.h"

namespace Slideshow {
    class ScriptFile : public File {
        private:
            std::ifstream _file;
            bool read_line(std::vector<std::string> &);
        protected:
            bool get_inst(std::vector<Instruction*> &);
        public:
            ScriptFile(const char *);
            ~ScriptFile();
            int run(GContext &);
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
