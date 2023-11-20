#pragma once
#include "mdfile.h"

class ClientBase
{
public:
    static std::map <std::string,std::string> read(std::string way, std::string err_way);
    static std::string find(std::string &name, std::map< std::string, std::string > &all);
};
