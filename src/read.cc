/**
 * @file read.cc
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Contains function to read file contents.
 * @version 0.1
 * @date 2021-08-08
 * 
 * @copyright Copyright (c) 2021
 */

#include <iostream>
#include <string>
#include <fstream>

#include "error.h"

/**
 * @brief Reads a file and returns the contents as string.
 * 
 * @param path std::string - Path of the file to be read.
 * @return std::string - String of the file contents.
 */
std::string readFile(const std::string path)
{
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        error(-1, "Could not open file");
    }
    // this is fucked, I know the type but im lazy (:
    auto theFirstParameter = std::istreambuf_iterator<char>(inputFile);
    auto theSecondParameter = std::istreambuf_iterator<char>();
    return std::string(theFirstParameter, theSecondParameter);
}