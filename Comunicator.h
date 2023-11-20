#pragma once
#include "mdfile.h"

class Comunicator
{
public:
    int self_addr(int port);
    int client_addr(int s);
    int autorized(int work_sock, std::string file_name,std::map <std::string,std::string> &all_names);
};
