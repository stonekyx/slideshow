#ifndef INSTRUCTION_H

#define INSTRUCTION_H

#include <vector>
#include <string>
#include <map>

#include <SDL.h>

#include "gcontext.h"

namespace Slideshow {
    class Instruction {
        public:
            //Plugins derives from this class, so they'll have
            //this typedef too.
            typedef bool (*explain_t)(std::vector<std::string>, Instruction *&);
            typedef explain_t (*explain_gen_t)();
        private:
            static std::vector<explain_t> *instlist;
            static void init_instlist();
            static std::string *prms_pp(std::vector<std::string> &);
            static std::map<std::string, Instruction *> inst_by_id;
        protected:
            Instruction() {}
            int parse_coor(const std::string &);
        public:
            virtual ~Instruction() {};
            virtual int run(GContext &)=0;
            virtual bool runback(GContext &) {
                return false;
            }
            virtual void get_point(int *x, int *y) {
                *x = *y = 0;
            }
            virtual void get_size(int *w, int *h) {
                *w = *h = 0;
            }
            virtual bool will_clear_screen() {
                return false;
            }
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
