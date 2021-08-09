/**
 * @file stack.h
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Header for the stack.
 * @version 0.1
 * @date 2021-08-09
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef STACK_H_
#define STACK_H_

#include <string>
#include <vector>
#include <map>

#include "variable.h"
#include "parse.h"

class Stack 
{
private:
    std::vector<std::string> stringConstants;
    std::map<std::string, Variable> vars;

public:
    Stack(std::vector<std::string> sc);

    Variable resolveSymbol(std::string symbol);

};

#endif