/**
 * @file strutils.h
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Header for string utilities used across the codebase.
 * @version 0.1
 * @date 2021-08-07
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>
#include <string>

/**
 * @brief Prints an error in red to console and exits the program.
 * 
 * @param n int - Line number error occurred on, -1 for no line.
 * @param s std::string - Error message.
 */
void error(int n, std::string s);

#endif
