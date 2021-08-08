/**
 * @file error.cpp
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Error handling
 * @version 0.1
 * @date 2021-08-07
 * 
 * @copyright Copyright (c) 2021
 */

#include <iostream>
#include <string>

/**
 * @brief Prints an error in red to console and exits the program.
 * 
 * @param n int - Line number error occurred on, -1 for no line.
 * @param s std::string - Error message.
 */
void error(int n, std::string s) 
{
    if (n >= 0) {
        printf("\u001b[31mError: \"%s\" on line %d\u001b[0m\n", s.c_str(), n);
    } else {
        printf("\u001b[31mError: \"%s\"\u001b[0m\n", s.c_str());
    }
    exit(0);
}