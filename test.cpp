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
    TEST(boost1_2_test){
        const char* test_argv[] = {"name", "-l", "err.txt", "-f", "base.txt", "-d", "33333"};
        CHECK_THROW(User_Interface(7, (char**)test_argv), boost::program_options::error);
    }
    TEST(boost2_test){
        const char* test_argv[] = {"name", "-p", "abc", "-l", "err.txt", "-f", "base.txt"};
        CHECK_THROW(User_Interface(7, (char**)test_argv), boost::program_options::error);
    }
    TEST(boost2_1_test){
        const char* test_argv[] = {"name", "-p", "абв"};
        CHECK_THROW(User_Interface(3, (char**)test_argv), boost::program_options::error);
    }
    TEST(true_test){
        const char* test_argv[] = {"name", " "};
        User_Interface ui(2, (char**)test_argv);
        CHECK(true); 
    }
    TEST(ui_norm){
        const char* test_argv[] = {"name", "-p", "33333", "-l", "err.txt", "-f", "base.txt"};
        User_Interface ui(7, (char**)test_argv);
        bool flag = false;
        if (ui.LogWrite == "err.txt" and ui.file == "base.txt" and ui.port == 33333)
        {
            flag = true;
        }
        CHECK(flag);
    }
    TEST(ui_norm_1){
        const char* test_argv[] = {"name", "-p", "77777", "-l", "абв", "-f", "абв"};
        User_Interface ui(7, (char**)test_argv);
        bool flag = false;
        if (ui.LogWrite == "абв" and ui.file == "абв" and ui.port == 77777)
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
    TEST(boost3_1_test){
        const char* test_argv[] = {"name", "-l", "err.txt", "-f", "base.txt", "-p", "33333","-d","abc"};
        CHECK_THROW(User_Interface(9, (char**)test_argv), boost::program_options::error);
    }
}

SUITE(client_base){
    TEST(cb1_1){
        std::string way = "CB_test.txt";
        std::string err_way = "error.txt";
        CHECK_THROW(ClientBase::read(way,err_way), ServerError); 
    }
    TEST(cb1_2){
        std::string way = "CB.txt";
        std::string err_way = "error.txt";
        CHECK_THROW(ClientBase::read(way,err_way), ServerError); 
    }
    TEST(cb1_3){
        std::string way = "base.txt";
        std::string err_way = "error.txt";
        ClientBase::read(way,err_way);
        CHECK(true); 
    }
    TEST(cb1_4){
        std::string way = "test_base.txt";
        std::string name = "uder";
        std::map< std::string, std::string > all = ClientBase::read("base.txt","error.txt");
        std::map< std::string, std::string > test ={{"uer", "P@ssW0rd"}, {"us", "P@ssW0rd"}, {"user", "P@ssW0rd"}};
        CHECK(all == test); 
    }   
    TEST(cb2_1){
        std::string way = "test_base.txt";
        std::string name = "agent";
        std::map< std::string, std::string > all = ClientBase::read(way,"error.txt");
        CHECK_THROW(ClientBase::find(name, all), ServerError); 
    }
    TEST(cb2_2){
        std::string way = "test_base.txt";
        std::string name = "user";
        std::map< std::string, std::string > all = ClientBase::read(way,"error.txt");
        ClientBase::find(name, all);
        CHECK(true); 
    }
}

int main() {
    RunSuite("UserInterface");
    RunSuite("client_base");
    return 0;
    
}
