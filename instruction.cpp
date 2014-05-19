#include <cstdio>

#include <dlfcn.h>
#include <dirent.h>
#include <sys/stat.h>

#include "instruction.h"

#define INST_PLUGIN_PATH "inst_plugins"

using namespace Slideshow;
using namespace std;

vector<Instruction::explain_t> *Instruction::instlist = NULL;

void Instruction::init_instlist()
{
    if(Instruction::instlist) {
        return;
    }
    Instruction::instlist = new vector<explain_t>();

    {
        DIR *inst_plugins = opendir(INST_PLUGIN_PATH);
        if(!inst_plugins) return;
        struct dirent *entry;

        while((entry = readdir(inst_plugins))) {
            static char path[1024];
            snprintf(path, sizeof(path), "%s/%s", INST_PLUGIN_PATH, entry->d_name);
            void *handle = dlopen(path, RTLD_LAZY);
            if(!handle) {
                continue;
            }
            dlerror();
            explain_gen_t func = (explain_gen_t)dlsym(handle, "get_explain");
            if(func && !dlerror()) {
                instlist->push_back(func());
            }
        }
    }
    //in each file: extern "C" explain_t explain = &Inst::explain;
    //no need for constructor in each plugin.
}

bool Instruction::explain(vector<string> prms, Instruction *&res)
{
    if(NULL == Instruction::instlist) {
        Instruction::init_instlist();
    }
    for(vector<explain_t>::iterator it = instlist->begin();
            it!=instlist->end(); it++) {
        if((*it)(prms, res)) {
            return true;
        }
    }
    return false;
}

//---------------------dlsym interface-------------------

extern "C"
Instruction::explain_t get_explain()
{
    return Instruction::explain;
}
