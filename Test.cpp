/**
 *
 * AUTHORS: Ori Darshan
 *
 * Date: 2021-03
 */

#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;


Notebook notebook1;
Notebook notebook2;

// Commands that should generate errors
TEST_CASE("Good Input")
{
    //#1 write to the notebook:
    CHECK_NOTHROW(notebook1.write(0,0,0,Direction::Horizontal,"Hello!"));
    //#1.1 unlimited page count
    CHECK_NOTHROW(notebook1.write(10000,0,0,Direction::Horizontal,"World"));
    //#1.2 unlimited line count
    CHECK_NOTHROW(notebook1.write(0,10000,0,Direction::Horizontal,"place holder"));
    //#1.3 100 characters per line
    string s =  "0123456789"
                "0123456789"
                "0123456789"
                "0123456789"
                "0123456789"
                "0123456789"
                "0123456789"
                "0123456789"
                "0123456789"
                "0123456789";// 100 characters string
    CHECK_NOTHROW(notebook1.write(0,1,0,Direction::Horizontal,s));
    //#1.4 15 characters from column 85 (85-99)
    CHECK_NOTHROW(notebook1.write(0,2,85,Direction::Horizontal,"123456789012345"));
    //#1.5 10 character from 75 at the same line
    CHECK_NOTHROW(notebook1.write(0,2,75,Direction::Horizontal,"1234567890"));
    //#1.6 can write all relevant chars
    for (int i = 33; i < 126; i++)//TODO finalize bounaries
    {
        char c = (char)i;
        CHECK_NOTHROW(notebook1.write(0, i, 0, Direction::Horizontal, (string)c));
    }
    //#1.7 write vertically
    CHECK_NOTHROW(notebook2.write(0,0,0,Direction::Vertical,"Hello!"));
    //#1.8 write more than 100 character vertically
    CHECK_NOTHROW(notebook2.write(0,0,1,Direction::Vertical,s+"0"));
    //#1.9 write '_'
    CHECK_NOTHROW(notebook1.write(100, 0 , 0, Direction::Horizontal, "___"));
    //#1.10 write over written '_'
    CHECK_NOTHROW(notebook1.write(100, 0 , 0, Direction::Horizontal, "Hi"));
    //#1.10 cross writing using '_'
    CHECK_NOTHROW(notebook1.write(101, 1 , 0, Direction::Horizontal, "A_C"));
    CHECK_NOTHROW(notebook1.write(101, 0 , 1, Direction::Vertical, "ABC"));
    /* this will look like:
    _A___
    ABC__
    _C___
    */

    //#2 read from the notebook
    CHECK(notebook1.read(0,0,0,Direction::Horizontal,6) == "Hello!");
    //#2.1 read empty parts
    CHECK(notebook1.read(0, 0, 55, Direction::Horizontal, 4) == "");
    //#1
    
   
}

TEST_CASE("Error Generating"){
    //CHECK_NOTHROW(notebook.write(10000, 10000, 98, "*"));
}