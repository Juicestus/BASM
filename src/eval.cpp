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
 * @brief Add a new pointer to the jump pointers.
 * 
 * @param pointer 
 */
void JumpPointers::addPointer(std::string pointer) 
{
    JumpPointers::pointers.push_back(pointer);
}

/**
 * @brief Return the index of the searched pointer.
 * 
 * @param pointer 
 * @return int 
 */
int JumpPointers::lineOfPointer(std::string pointer) 
{
    for (int i = 0; i < JumpPointers::pointers.size(); i++) {
        if (JumpPointers::pointers[i] == pointer) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Evaluates the expression.
 * 
 * @param stack Stack - The memory stack object.
 * @param lines std::vector&lt;Line&gt; - The parse expression lines.
 */
void evaluate(Stack stack, std::vector<Line> lines)
{
    JumpPointers pointers;

    for (int n=0; n < lines.size(); n++)
    {
        Line line = lines[n]; 
        std::cout << line.command << std::endl;
        pointers.addPointer(line.pointer);

        std::vector<Variable> args;
        for (std::string arg : line.arguments) {
            Variable carg = stack.resolveSymbol(arg);
            if (carg.type == Type::NONE) {
                //error(n, "Argument '" + arg + "' cannot be resolved");
            }
            args.push_back(carg);
        }

        for (Variable arg : args) {
            arg.repr();
        }

    }
}