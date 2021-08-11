/**
 * @file stack.cc
 * @author Justus Languell (jus@gtsbr.org)
 * @brief The memory stack and symbol resolver.
 * @version 0.1
 * @date 2021-08-09
 * 
 * @copyright Copyright (c) 2021
 */

#include <string>
#include <vector>
#include <map>
#include <regex>

#include "variable.h"
#include "stack.h"

/**
 * @brief Construct a new Stack object with stored strings.
 * 
 * @param sc std::vector&lt;std::string&gt; - String constants vector
 */
Stack::Stack(std::vector<std::string> sc) {
    Stack::stringConstants = sc;
}

/**
 * @brief Resolve a symbol into a variable
 * 
 * @param symbol std::string - Symbol to be resolved
 * @return Variable - Resolved symbol
 */
Variable Stack::resolveSymbol(std::string symbol)
{
    if (symbol.substr(0, STR_REPL.length()) == STR_REPL) {
        int identifier = std::stoi(symbol.substr(STR_REPL.length()));
        return Variable(stringConstants[identifier]);
    } else if (symbol == "true") {
        return Variable(true);
    } else if (symbol == "false") {
        return Variable(false);
    } else if (symbol == "null") {
        return Variable();
    } else if (std::regex_match(symbol, intMatch)) {
        return Variable((long) std::stoi(symbol));
    } else if (std::regex_match(symbol, floatMatch)) {
        return Variable(std::stof(symbol));
    } else if (symbol[0] == '!') {
        Variable v = Variable();
        v.setJP(symbol);
        return v;
    } else {
        if (Stack::vars.find(symbol) != Stack::vars.end()) {
            return Stack::vars[symbol];
        } else {
            return Variable();
        }
    }
}

int Stack::pushVar(std::string name, Variable variable) {
    // Check for stuff ig?
    if (Stack::vars.find(name) != Stack::vars.end()) {
        if (name[0] == '$') {
            return -1;
        } else {
            Stack::vars[name] = variable;
            return 0;
        }
    } else {
        Stack::vars[name] = variable;
        return 0;
    }
}
