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
#include <regex>

#include "variable.h"
#include "parse.h"

const std::string INT_REGEX = "[+-]?[0-9]+";
//const std::string FLOAT_REGEX = "[+-]?[0-9]+(\\.[0-9]+)?([Ee][+-]?[0-9]+)?";
const std::string FLOAT_REGEX = "^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$";

const std::regex intMatch(INT_REGEX);
const std::regex floatMatch(FLOAT_REGEX);

class Stack 
{
private:
    std::vector<std::string> stringConstants;
    std::map<std::string, Variable> vars;

public:
    Stack(std::vector<std::string> sc);

    Variable resolveSymbol(std::string symbol);
    int pushVar(std::string name, Variable variable);
};

#endif