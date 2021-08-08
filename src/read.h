/**
 * @file read.h
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Header for function to read file contents.
 * @version 0.1
 * @date 2021-08-08
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef READ_H_
#define READ_H_

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
std::string readFile(const std::string path);

#endif