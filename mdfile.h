#pragma once
#include <netinet/in.h>
#include <map>
#include <limits>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <fstream>
#include <string>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <boost/program_options.hpp>
#include <memory>
#include <random>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
using namespace CryptoPP;
#include <cryptopp/md5.h>
#include<exception>
#include<ctime>
class ServerError: public std::runtime_error{
    public:
    ServerError(const char* msg): std::runtime_error(msg){};
    ServerError(const std::string &msg): std::runtime_error(msg){};
};
class LogWriter
{
public:
    static void log(std::string &way, std::string msg );
};
