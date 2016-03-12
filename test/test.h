#ifndef TEST_H
#define TEST_H

#include <iostream>
#include "persistence/pmanager_test.h"

using namespace std;

/* Unit testing class */

class Test
{
public:
    Test();
    void test_all();
    void test_persistence();
    /* fflush needed to see the output on the Application Output of QT Creator */
    static void print_green(string s) { printf("\033[32m%s\033[39m", s.c_str()); fflush(stdout); }
    static void print_red(string s) { printf("\033[31m%s\033[39m", s.c_str()); fflush(stdout); }
    static void print(string s) { printf("%s", s.c_str()); fflush(stdout); }
};

#endif // TEST_H
