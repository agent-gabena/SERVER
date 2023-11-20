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
SUITE(KeyTest){
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
    TEST(ui1_test){
        const char* test_argv[] = {"name", "-p", "33333", "-l", "err.txt"};
        User_Interface ui(5, (char**)test_argv);
        CHECK_THROW(ui(), ServerError);
    }
    TEST(ui2_test){
        const char* test_argv[] = {"name", "-f", "base.txt", "-l", "err.txt"};
        User_Interface ui(5, (char**)test_argv);
        CHECK_THROW(ui(), ServerError);
    }
    TEST(ui3_test){
        const char* test_argv[] = {"name", "-p", "33333", "-l", "err.txt"};
        User_Interface ui(5, (char**)test_argv);
        CHECK_THROW(ui(), ServerError);
    }
}

SUITE(client_base){
    TEST(second_test){
        std::string way = "CB_test.txt";
        std::string err_way = "err.txt";
        CHECK_THROW(ClientBase::read(way,err_way), ServerError); 
    }
}

int main() {
    RunSuite("KeyTest");
    return 0;
    
}