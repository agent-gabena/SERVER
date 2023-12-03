#define UNIT_TEST
#include "mdfile.h"
#include "Calculator.h"
#pragma once
namespace po = boost::program_options;
class User_Interface
{
////for test
#ifdef UNIT_TEST
public:
    std::string file;
    std::string LogWrite;
    int port;
#else
private:
#endif
    po::options_description descr;
    po::variables_map vm;
    //std::string file;
    //std::string LogWrite;
    //int port;
    void Input();

public:
    bool flag = true;
    User_Interface() = delete;
    User_Interface(int argc, char **argv);
    void operator()();
};
