#ifndef INSTRUCTION_H

#define INSTRUCTION_H

#include <vector>
#include <string>

#include <SDL.h>

namespace Slideshow {
    class Instruction {
        public:
            //Plugins derives from this class, so they'll have
            //this typedef too.
            typedef bool (*explain_t)(std::vector<std::string>, Instruction *&);
        private:
            typedef explain_t (*explain_gen_t)();
            std::string name;
            static std::vector<explain_t> *instlist;
            static void init_instlist();
        protected:
            Instruction() {}
        public:
            virtual ~Instruction() {};
            const std::string &get_name() {
                return name;
            }
            virtual void run(SDL_Window *, SDL_Renderer *)=0;
            static bool explain(std::vector<std::string>, Instruction *&);
    };
}

#endif
