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

        pointers.addPointer(line.pointer);

        std::vector<Variable> args;
        for (std::string arg : line.arguments) {
            Variable carg = stack.resolveSymbol(arg);
            if (carg.type == Type::NONE) {
                //error(n, "Argument '" + arg + "' cannot be resolved");
            }
            args.push_back(carg);
        }

        //for (Variable arg : args) {
            //arg.repr();
        //}

        if (line.command == "") {
            error(n, "No command given");
        }

        /**
         * @brief Set function
         * Set return to first and only argument
         * 
         * Todo: Set multiple return values
         * Todo: If multiple return values and multiple args,
         * Todo:  set 1-1 and if there are issues figure em out
         */
        else if (line.command == "set") {
            stack.pushVar(line.returns[0], args[0]);
        }

        /**
         * @brief Add function
         * Takes in n args of type int or float
         * Returns int or float sum of args
         */
        else if (line.command == "add") 
        {
            bool noFloats = true;
            float fsum;
            for (int i=0; i < args.size(); i++) {
                Variable var = args[i];
                if (var.type == Type::FLOAT) {
                    noFloats = false;
                    fsum += var.floatVal;
                } else if (var.type == Type::INT) {
                    fsum += (float) var.intVal;
                } else {
                    error(n, "Argument '" + line.arguments[i] 
                          + "' is not of valid type INT or FLOAT");
                }
            }
            if (noFloats) {
                stack.pushVar(line.returns[0], (long) fsum);
            } else {
                stack.pushVar(line.returns[0], fsum);
            }
        }

        /**
         * @brief Jump function
         * Takes in two args, boolean to jump or not, and 
         * goto pointer. Jumps to the goto pointer.
         */
        else if (line.command == "jump") {
            if (args[0].type == Type::BOOL
                && args[1].type == Type::JUMP) {
                if (args[0].boolVal) {
                    n = pointers.lineOfPointer(args[1].jpVal) - 1;
                }
            } else {
                error(n, "Either non valid boolean or jump/goto pointer!");
            }
        }

        /**
         * @brief print function
         * Prints all args in sequence with no break
         */
        else if (line.command == "print") {
            std::string output = "";
            for (int i=0; i < args.size(); i++) {
                output += args[i].printable();
            }
            std::cout << output;
        }
    }
}