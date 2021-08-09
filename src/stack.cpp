/**
 * @file stack.cpp
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
    } else {
        return Variable();
    }
}
