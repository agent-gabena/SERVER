#pragma once
#include "mdfile.h"

class Comunicator
{
public:
    int self_addr(int port, std::string &err_way);
    int client_addr(int s, std::string &err_way);
    int autorized(int work_sock, std::string file_name,std::map <std::string,std::string> &all_names, std::string &err_way);
};
