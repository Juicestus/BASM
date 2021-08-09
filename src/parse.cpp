/**
 * @file parse.cpp
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Functions to parse the code into usable representation.
 * @version 0.2
 * @date 2021-08-08
 * 
 * @copyright Copyright (c) 2021
 */

#include <iostream>
#include <string>
#include <vector>

#include "error.h"
#include "parse.h"

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
 * @return std::vector&lt;std::string&gt; - Vector of seperated strings.
 */
std::vector<std::string> 
        splitString(std::string subject, const char delimiter)
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
    tokens.push_back(currentToken);
    return tokens;
}

/**
 * @brief Char in string
 * 
 * @param c char - The character to look for.
 * @param s std::string - The string to look in.
 */
bool charInString(char c, std::string s) 
{
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Replaces string literals with special identifiers and stores them.
 * 
 * @param s std::string - String of source code
 * @param delim char - String delimiter character
 * @return std::pair&lt;std::string, std::vector&lt;std::string&gt;&gt;
 */
std::pair<std::string, std::vector<std::string>> 
        removeDemlimStr(std::string s, char delim)
{
    std::vector<std::string> removedStrings;
    std::string stringless = "";
    bool partOfString = false;
    std::string curString = "";
    char prevChar = ' '; 
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == delim && prevChar != '\\') {
            if (partOfString) {
                removedStrings.push_back(curString);
                curString = "";
            } else {
                stringless += (STR_REPL + std::to_string(removedStrings.size()));
            }
            partOfString = !partOfString;
        } else {
            if (partOfString) {
                curString += s[i];
            } else {
                stringless += s[i];
            }
        }
        prevChar = s[i];
    }
    return std::make_pair(stringless, removedStrings);
}

/**
 * @brief Remove spaces from the code.
 * 
 * @param s std::stirng - Code w/ spaces.
 * @return std::string - Code w/o spaces.
 */
std::string removeSpaces(std::string s) 
{
    std::string result = "";
    for (char c : s) {
        if (c != ' ' && c != '\t') result += c;
    }
    return result;
}

/**
 * @brief Parse source code into vector of line objects.
 * 
 * @param code std::string - Source code.
 * @return std::vector &lt; Line &gt; - The parsed lines of code.
 */
std::pair<std::vector<std::string>, std::vector<Line>> 
        parseLines(std::string code) 
{
    code = removeComments(code, '(', ')');
    code = replaceString(code, "\n", "");
    code = removeSpaces(code);

    std::pair<std::string, std::vector<std::string>> 
            stringlessPair = removeDemlimStr(code, '"');

    std::string stringless = stringlessPair.first;

    std::vector<std::string> rawLines = splitString(stringless, ';');
    std::vector<Line> lines;

    char delim = ':';
    char argdelim = ',';
    std::string currentReturnPoint = "";
    for (int n = 0; n < rawLines.size(); n++) 
    {
        std::string line = rawLines[n];
        Line lineData;

        // ?
        //(!charInString(delim, line)) || currentReturnPoint = line;
        if (!charInString(delim, line)) {
            currentReturnPoint = line;
        } else {
            std::vector<std::string> parts = splitString(line, delim);
            lineData.pointer = currentReturnPoint;

            if (parts.size() == 2) {
                lineData.command = parts[0];
                lineData.arguments = splitString(parts[1], argdelim);
            } else if (parts.size() == 3) {
                lineData.command = parts[0];
                lineData.arguments = splitString(parts[1], argdelim);
                lineData.returns = splitString(parts[2], argdelim);
            } else {
                error(n, "Invalid line structure syntax");
            }

            currentReturnPoint = "";
            lines.push_back(lineData);
        }
    }
    return std::make_pair(stringlessPair.second, lines);
}

// This is the first BASM program ever written
/*
( Count to 100 )

set : 0. : counter ;
add : counter, 1 : counter ;
!pointer ;
print : counter, "\n" ;
lteq : counter, 100 : shouldJump ;
jump : souldJump, !pointer ;
*/