#include <cstdio>
#include <cctype>

#include <dlfcn.h>
#include <dirent.h>
#include <sys/stat.h>

#include <boost/lexical_cast.hpp>

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
            void *handle = dlopen(path, RTLD_LAZY | RTLD_GLOBAL);
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

//TODO: pass window size from playctl.

map<string, Instruction *> Instruction::inst_by_id;

string *Instruction::prms_pp(vector<string> &prms)
{
    string *id = NULL;
    bool quit = false;
    while(!quit) {
        quit = true;
        for(vector<string>::iterator it = prms.begin();
                it!=prms.end(); it++) {
            if(it->find("id=")==0) {
                id = new string(it->substr(3));
                prms.erase(it);
                quit = false;
                break;
            }
        }
    }
    return id;
}

int Instruction::parse_coor(const string &id)
{
    if((tolower(id[0])!='x' && tolower(id[0])!='y') ||
            (id[1]!=':' && id[2]!=':')) {
        return boost::lexical_cast<int>(id);
    }
    Instruction *inst;
    if(id[1]==':') {
        inst = inst_by_id[id.substr(2)];
    } else {
        inst = inst_by_id[id.substr(3)];
    }
    if(inst==NULL) {
        return -1;
    }
    int x, y;
    inst->get_point(&x, &y);
    if(isupper(id[0])) {
        int w, h;
        inst->get_size(&w, &h);
        x+=w; y+=h;
    }
    if(id[1]!=':') {
        //"x?:" form
        int w, h;
        this->get_size(&w, &h);
        int type = id[1]-'0';
        switch(type) {
            case 1: //top left
                break;
            case 2: //top right
                x -= w; break;
            case 3: //bottom left
                y -= h; break;
            case 4: //bottom right
                x -= w; y -= h; break;
            case 5: //middle
                x -= w/2; y -= h/2; break;
            default: ;
        }
    }
    if(tolower(id[0])=='x') {
        return x;
    } else {
        return y;
    }
}

bool Instruction::explain(vector<string> prms, Instruction *&res)
{
    if(NULL == Instruction::instlist) {
        Instruction::init_instlist();
    }
    string *id = Instruction::prms_pp(prms);
    for(vector<explain_t>::iterator it = instlist->begin();
            it!=instlist->end(); it++) {
        if((*it)(prms, res)) {
            if(id) {
                inst_by_id[*id] = res;
            }
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
