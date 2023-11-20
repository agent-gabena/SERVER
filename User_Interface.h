#include "mdfile.h"
#include "Calculator.h"
#pragma once
namespace po = boost::program_options;
class User_Interface
{
private:
    po::options_description descr;
    po::variables_map vm;
    std::string file;
    std::string LogWrite;
    int port;
    void Input();
public:
    bool flag = true;
    User_Interface() = delete;
    User_Interface(int argc, char **argv);
    void operator()();
};
