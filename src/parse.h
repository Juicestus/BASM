/**
 * @file parse.h
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Header for functions to parse the code into usable representation.
 * @version 0.2
 * @date 2021-08-08
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef STRUTILS_H_
#define STRUTILS_H_

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Removes comments from the file content.
 * 
 * @param code std::string - Code with comments.
 * @param open char - Character to delimit opening comment.
 * @param close char - Character to delimit closing comment.
 * @return std::string - Code with comments removed.
 */
std::string removeComments(std::string code, char open, char close);

/**
 * @brief Replace all instances of search with replace in subject.
 * 
 * @param subject std::string - The string to replace isntances with.
 * @param search std::string - The string to search for.
 * @param replace std::string - The string to replace with.
 * @return std::string - Subject with instances of search replaced with replace.
 */
std::string replaceString(std::string subject, const std::string& search,
                          const std::string& replace);

/**
 * @brief 
 * 
 * @param subject std::string - The string to be parsed.
 * @param delimiter char - The delimiter character.
 * @return std::vector<std::string> - Vector of seperated strings.
 */
std::vector<std::string> splitString(std::string subject, const char delimiter);

/**
 * @brief Char in string
 * 
 * @param c char - The character to look for.
 * @param s std::string - The string to look in.
 */
bool charInString(char c, std::string s);

/**
 * @brief Replaces string literals with special identifiers and stores them.
 * 
 * @param s std::string - String of source code
 * @param delim char - String delimiter character
 * @return std::pair<std::string, std::vector<std::string>> 
 */
std::pair<std::string, std::vector<std::string>> 
        removeDemlimStr(std::string s, char delim);

/**
 * @brief Structure to hold the relavant information from a line of code.
 */
struct Line {
    std::string pointer;
    std::string command;
    std::vector<std::string> arguments;
    std::vector<std::string> returns;
};

/**
 * @brief Parse source code into vector of line objects.
 * 
 * @param code std::string - Source code.
 * @return std::vector<Line> - The parsed lines of code.
 */
std::pair<std::vector<std::string>, std::vector<Line>> 
        parseLines(std::string code);

#endif