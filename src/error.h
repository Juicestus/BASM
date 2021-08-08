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

#include "parse.h"

/**
 * @brief Prints an error in red to console and exits the program.
 * 
 * @param n int - Line number error occurred on, -1 for no line.
 * @param s std::string - Error message.
 */
void error(int n, std::string s);

/**
 * @brief Formats a string vector
 * 
 * @param sv std::vector&lt;std::string&gt - String vector.
 * @returns std::string - Printable array string.
 */
std::string printableVector(std::vector<std::string> sv);

/**
 * @brief Prints lines of code and relevant information
 * 
 * @param lines std:vector&lt;std::string&gt; - Lines of code.
 */
void printLines(std::vector<Line> lines);

#endif
