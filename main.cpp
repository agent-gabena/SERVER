#include "User_Interface.h"
int main(int argc, char *argv[])
{
    try
    {
        User_Interface ui(argc,argv);
        ui();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
