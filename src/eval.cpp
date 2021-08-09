/**
 * @file eval.cpp
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Evaluates the expressions.
 * @version 0.1
 * @date 2021-08-09
 * 
 * @copyright Copyright (c) 2021
 */

#include <string>
#include <vector>

#include "parse.h"
#include "error.h"
#include "variable.h"
#include "stack.h"

#include "eval.h"

/**
 * @brief Evaluates the expression.
 * 
 * @param stack Stack - The memory stack object.
 * @param lines std::vector&lt;Line&gt; - The parse expression lines.
 */
void evaluate(Stack stack, std::vector<Line> lines)
{
    for (int n=0; n < lines.size(); n++)
    {
        Line line = lines[n];
        
        std::cout << line.command << std::endl;
        std::vector<Variable> args;
        for (std::string arg : line.arguments) {
            args.push_back(stack.resolveSymbol(arg));
        }
        for (Variable arg : args) {
            arg.repr();
        }

    }
}