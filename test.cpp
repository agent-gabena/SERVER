#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <string>
#include <UnitTest++/TestReporterStdout.h>
#include "Calculator.h"
#include "client_base.h"
#include "Comunicator.h"
#include "mdfile.h"
#include "User_Interface.h"
auto RunSuite (const char* SuiteName)
{ 
    UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf(UnitTest::Test::GetTestList(),
                                SuiteName,
                                UnitTest::True(),0);
}
SUITE(UserInterface){
    TEST(boost1_test){
        const char* test_argv[] = {"name", "-k", "98"};
        CHECK_THROW(User_Interface(3, (char**)test_argv), boost::program_options::error);
    }
    TEST(boost2_test){
        const char* test_argv[] = {"name", "-p", "abc", "-l", "err.txt", "-f", "base.txt"};
        CHECK_THROW(User_Interface(7, (char**)test_argv), boost::program_options::error);
    }
    TEST(true_test){
        const char* test_argv[] = {"name", " "};
        User_Interface ui(2, (char**)test_argv);
        CHECK(true); 
    }
    TEST(ui){
        const char* test_argv[] = {"name", "-p", "33333", "-l", "абв", "-f", "абв"};
        User_Interface ui(7, (char**)test_argv);
        bool flag = false;
        if (ui.LogWrite == "абв" and ui.file == "абв" and ui.port == 33333)
        {
            flag = true;
        }
        
        CHECK(flag);
    }
    TEST(ui1){
        const char* test_argv[] = {"name", "-p", "33333", "-l", "err.txt"};
        User_Interface ui(5, (char**)test_argv);
        CHECK_THROW(ui(), ServerError);
    }
    TEST(ui2){
        const char* test_argv[] = {"name", "-f", "base.txt", "-l", "err.txt"};
        User_Interface ui(5, (char**)test_argv);
        CHECK_THROW(ui(), ServerError);
    }
    TEST(ui3){
        const char* test_argv[] = {"name", "-p", "33333", "-f", "base.txt"};
        User_Interface ui(5, (char**)test_argv);
        CHECK_THROW(ui(), ServerError);
    }
}

SUITE(client_base){
    TEST(cb){
        std::string way = "CB_test.txt";
        std::string err_way = "error.txt";
        CHECK_THROW(ClientBase::read(way,err_way), ServerError); 
    }
    TEST(cb1){
        std::string way = "CB_test.txt";
        std::string err_way = "error.txt";
        CHECK_THROW(ClientBase::read(way,err_way), ServerError); 
    }   
    TEST(cb2){
        std::string way = "CB.txt";
        std::string err_way = "error.txt";
        CHECK_THROW(ClientBase::read(way,err_way), ServerError); 
    }
    TEST(cb3){
        bool flag = false;
        std::map< std::string, std::string > all = ClientBase::read("base.txt","error.txt");
        std::map< std::string, std::string > test{{"uer", "P@ssW0rd"}, {"us", "P@ssW0rd"}, {"user", "P@ssW0rd"}};
        for ( auto element : all )
        {
            flag = false;
            for ( auto t_el : test )
            {   
                if (element.first == t_el.first and element.second == t_el.second )
                {
                    flag = true;
                }
            }
        }
        CHECK(flag);
    }
    TEST(cb4){
        std::string way = "CB_test.txt";
        std::string name = "uder";
        std::map< std::string, std::string > all = ClientBase::read("base.txt","error.txt");
        CHECK_THROW(ClientBase::find(name, all), ServerError); 
    }

}

int main() {
    RunSuite("UserInterface");
    //RunSuite("client_base");
    return 0;
    
}