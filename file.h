#ifndef FILE_H

#define FILE_H

#include <vector>

#include "instruction.h"

namespace Slideshow {
    class File : public Instruction {
        private:
        protected:
            std::vector<Instruction*> inst;
            std::vector<Instruction*>::iterator inst_it;
            Instruction::explain_t inst_abs_explain;

            File() {}
            virtual bool get_inst(std::vector<Instruction*> &)=0;
        public:
            virtual ~File() {};
            virtual void repaint_to(std::vector<Instruction*>::iterator, GContext &)=0;
    };
    typedef File *(*file_creator_t)(const char *);
    typedef void (*file_destroyer_t)(File *);
}

#endif
