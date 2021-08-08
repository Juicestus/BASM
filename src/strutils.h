/**
 * @file strutils.h
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Header for string utilities used across the codebase.
 * @version 0.1
 * @date 2021-08-07
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

#endif