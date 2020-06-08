#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include "Sys.h"

namespace game
{
    extern bool Init(const char *);
    
    extern bool LoadServerParameters(const char* filepath);
    
    extern std::map<std::string, double> paramNumbers;
    extern std::map<std::string, std::string> paramStrs;

};

#endif

