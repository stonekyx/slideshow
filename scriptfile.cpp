#define SCRIPTFILE_IMPL

#include <iostream>
#include <exception>
#include <cstdio>
#include <dlfcn.h>

#include <boost/tokenizer.hpp>

#include "scriptfile.h"

using namespace Slideshow;
using namespace std;
using namespace boost;

bool ScriptFile::read_line(vector<string> &res)
{
    string s;
    if(!std::getline(_file, s)) {
        return false;
    }
    escaped_list_separator<char> sep("\\", " \t", "\"");
    tokenizer<escaped_list_separator<char> > tok(s, sep);
    for(tokenizer<escaped_list_separator<char> >::iterator it = tok.begin();
            it!=tok.end(); it++) {
        string raw_param = *it;
        if(it->find("//") != string::npos) {
            if(it->find("//") == 0) break;
            raw_param = it->substr(0, it->find("//"));
        }
        res.push_back(raw_param);
    }
    return true;
}

bool ScriptFile::get_inst(vector<Instruction*> &res)
{
    vector<string> prms;
    unsigned int linecnt=0;
    while(read_line(prms)) {
        linecnt++;
        Instruction *inst;
        if(!this->inst_abs_explain(prms, inst)) {
            cerr<<"Unable to explain line "<<linecnt<<endl;
            return false;
        }
        res.push_back(inst);
        prms.clear();
    }
    return true;
}

//------------------public interface--------------------

ScriptFile::ScriptFile(const char *filename)
{
    void *handle = dlopen("./instruction.so", RTLD_LAZY);
    if(!handle) {
        throw new exception();
    }
    this->inst_abs_explain = ((Instruction::explain_gen_t)dlsym(handle, "get_explain"))();
    _file.open(filename);
    if(!_file) {
        perror("ScriptFile constructor");
        throw new exception();
    }
    if(!this->get_inst(this->inst)) {
        throw new exception();
    }
    this->inst_it = this->inst.begin();
}

ScriptFile::~ScriptFile()
{
    cout<<"closing"<<endl;
    _file.close();
}

int ScriptFile::run(GContext &gc)
{
    int delay;
    while(inst_it!=inst.end() &&
            (delay=(*inst_it)->run(gc))==-2) {
        inst_it++;
    }
    if(inst_it==inst.end()) {
        return -2;
    }
    return delay;
}

bool ScriptFile::explain(vector<string> prms, Instruction *&inst)
{
    if(prms.size()<2 || prms[0].compare("include.script")) {
        return false;
    }
    inst = new ScriptFile(prms[1].c_str());
    return true;
}

//------------------dlsym interface---------------------

extern "C"
File *create_file_obj(const char *filename)
{
    return new ScriptFile(filename);
}

extern "C"
void destroy_file_obj(File *obj)
{
    delete obj;
}
