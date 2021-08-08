/**
 * @file basm.cpp
 * @author Justus Languell (jus@gtsbr.org)
 * @brief 
 * @version 0.1
 * @date 2021-08-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>
#include <vector>

#include "strutils.h"
#include "error.h"

/**
 * @brief Main function of course (:
 * 
 * @param argc int - Number of arguments.
 * @param argv *char[] - Array of arguments.
 * @return int - Exit code.
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        error(-1, "No input file specified.");
    } else {
        //std::string input = readFile(argv[1]);
    }
    return 0;

}
