/**
 * @file basm.cc
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

#include "variable.h"
#include "parse.h"
#include "error.h"
#include "read.h"
#include "stack.h"
#include "eval.h"

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
        std::string code = readFile(argv[1]);
        std::pair<std::vector<std::string>, std::vector<Line>> 
        linePair = parseLines(code);

        std::vector<std::string> strings = linePair.first;
        std::vector<Line> lines = linePair.second;

        Stack stack = Stack(strings);
        evaluate(stack, lines);

    }
    return 0;

}
