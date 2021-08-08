/**
 * @file strutils.cpp
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Code for string utilities used across the codebase.
 * @version 0.1
 * @date 2021-08-07
 * 
 * @copyright Copyright (c) 2021
 */

#include <iostream>
#include <string>
#include <vector>

#include "strutils.h"

/**
 * @brief Removes comments from the file content.
 * 
 * @param code std::string - Code with comments.
 * @param open char - Character to delimit opening comment.
 * @param close char - Character to delimit closing comment.
 * @return std::string - Code with comments removed.
 */
std::string removeComments(std::string code, char open, char close) 
{
    bool comment = false;
    std::string commentless = "";
    for (int i = 0; i < code.length(); i++) {
        char c = code[i];
        if (c == open) {
            comment = true;
        } else if (c == close) {
            comment = false;
        } else {
            if (!comment) {
                commentless += c;
            }
        }
    }
    return commentless;
}

/**
 * @brief Replace all instances of search with replace in subject.
 * 
 * @param subject std::string - The string to replace isntances with.
 * @param search std::string - The string to search for.
 * @param replace std::string - The string to replace with.
 * @return std::string - Subject with instances of search replaced with replace.
 */
std::string replaceString(std::string subject, const std::string& search,
                          const std::string& replace) 
{
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

/**
 * @brief 
 * 
 * @param subject std::string - The string to be parsed.
 * @param delimiter char - The delimiter character.
 * @return std::vector<std::string> - Vector of seperated strings.
 */
std::vector<std::string> splitString(std::string subject, const char delimiter)
{
    std::vector<std::string> tokens;
    std::string currentToken = "";
    for (int i = 0; i < subject.length(); i++) {
        if (subject[i] == delimiter) {
            if (currentToken != "") {
                tokens.push_back(currentToken);
            }
            currentToken = "";
        } else {
            currentToken += subject[i];
        }
    }
    return tokens;
}