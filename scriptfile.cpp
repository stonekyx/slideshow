#define SCRIPTFILE_IMPL

#include <iostream>
#include <boost/tokenizer.hpp>
#include <cstdio>

#include "scriptfile.h"

using namespace Slideshow;
using namespace std;
using namespace boost;

bool ScriptFile::read_line(vector<Parameter*> &res)
{
    string s;
    if(!std::getline(_file, s)) {
        return false;
    }
    char_separator<char> sep(" \t");
    tokenizer<char_separator<char> > tok(s, sep);
    for(tokenizer<char_separator<char> >::iterator it = tok.begin();
            it!=tok.end(); it++) {
        string raw_param = *it;
        if(it->find("//") != string::npos) {
            if(it->find("//") == 0) break;
            raw_param = it->substr(0, it->find("//"));
        }
        StrParameter *param = new StrParameter(raw_param);
        res.push_back(param);
    }
    return true;
}

//------------------public interface--------------------

ScriptFile::ScriptFile(const char *filename)
{
    _file.open(filename);
    if(!_file) {
        perror("ScriptFile constructor");
    }
}

ScriptFile::~ScriptFile()
{
    cout<<"closing"<<endl;
    _file.close();
}

bool ScriptFile::getSlides(vector<Slide*> &res)
{
    Slide *slide = new Slide();
    vector<Parameter*> prms;
    unsigned int linecnt=0;
    while(read_line(prms)) {
        linecnt++;
        Instruction *inst;
        if(!Instruction::explain(prms, inst)) {
            cerr<<"Unable to explain line "<<linecnt<<endl;
            return false;
        }
        if(dynamic_cast<Slide*>(inst)) {
            res.push_back(slide);
            slide = dynamic_cast<Slide*>(inst);
        } else {
            slide->add_inst(inst);
        }
        prms.clear();
    }
    res.push_back(slide);
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
