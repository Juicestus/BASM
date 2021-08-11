/**
 * @file error.cc
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Error handling
 * @version 0.2
 * @date 2021-08-07
 * 
 * @copyright Copyright (c) 2021
 */

#include <iostream>
#include <string>
#include <vector>

#include "error.h"
#include "parse.h"

/**
 * @brief Prints an error in red to console and exits the program.
 * 
 * @param n int - Line number error occurred on, -1 for no line.
 * @param s std::string - Error message.
 */
void error(int n, std::string s) 
{
    if (n >= 0) {
        printf("\n\u001b[31mError: \"%s\" on line %d\u001b[0m\n", s.c_str(), n + 1);
    } else {
        printf("\n\u001b[31mError: \"%s\"\u001b[0m\n", s.c_str());
    }
    exit(0);
}


/**
 * @brief Formats a string vector
 * 
 * @param sv std::vector&lt;std::string&gt - String vector.
 * @returns std::string - Printable array string.
 */
std::string printableVector(std::vector<std::string> sv) 
{
    if (sv.size() == 0) {
        return "[ ]";
    } else if (sv.size() == 1) {
        return "[ '" + sv[0] + "' ]";
    } else {
        std::string out = "[ '" + sv[0] + "'";
        for (int i = 1; i < sv.size(); i++) {
            out += (", '" + sv[i] + "'");
        }
        return out + " ]";
    }
}

/**
 * @brief Prints lines of code and relevant information
 * 
 * @param lines std:vector&lt;std::string&gt; - Lines of code.
 */
void printLines(std::vector<Line> lines) 
{
    for (int i = 0; i < lines.size(); i++) {
        std::cout << "Line #" << std::to_string(i) << std::endl;
        std::cout << "  Pointer: " << lines[i].pointer << std::endl;
        std::cout << "  Command: " << lines[i].command << std::endl;
        std::cout << "  Args: " << printableVector(lines[i].arguments)
                << std::endl;
        std::cout << "  Returns: " << printableVector(lines[i].returns)
                << std::endl;
    }
}