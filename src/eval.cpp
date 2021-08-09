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
    std::map<std::string, int> pointers;

    for (int n=0; n < lines.size(); n++)
    {
        Line line = lines[n]; 

        pointers[line.pointer] = n;

        std::vector<Variable> args;
        for (std::string arg : line.arguments) {
            Variable carg = stack.resolveSymbol(arg);
            if (carg.type == Type::NONE) {
                error(n, "Argument '" + arg + "' cannot be resolved");
            }
            args.push_back(carg);
        }

        //for (Variable arg : args) arg.repr();

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
            bool hasFloat = false;
            long isum = 0;
            float fsum = 0;
            for (int i=0; i < args.size(); i++) {
                Variable var = args[i];
                if (var.type == Type::FLOAT) {
                    hasFloat = true;
                    fsum = isum;
                    fsum += var.floatVal;
                } else if (var.type == Type::INT) {
                    if (hasFloat) {
                        fsum += (float) var.intVal;
                    } else {
                        isum += var.intVal;
                    }
                } else {
                    error(n, "Argument '" + line.arguments[i] 
                          + "' is not of valid type INT or FLOAT");
                }
            }
            if (hasFloat) {
                // idk even know if the variable constructor is required
                // it might construct in parameter call
                //stack.pushVar(line.returns[0], Variable((long) fsum));
                stack.pushVar(line.returns[0], Variable(fsum));
            } else {
                //stack.pushVar(line.returns[0], Variable(fsum));
                stack.pushVar(line.returns[0], Variable(isum));
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
                    n = pointers[args[1].jpVal] - 1;
                }
            } else {
                error(n, "Either non valid boolean or jump/goto pointer");
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

        /**
         * @brief lteq function
         * Sets only return bool to the less than or equal operation
         * between the first two args, ints or floats.
         */
        else if (line.command == "lteq") {
            if (args.size() == 2) {
                float firstVal;
                float secondVal;

                if (args[0].type == Type::INT) {
                    firstVal = (float) args[0].intVal;
                } else if (args[0].type == Type::FLOAT) {
                    firstVal = args[0].floatVal;
                } else {
                    error(n, "Argument 1 not valid numberical type");
                }

                if (args[1].type == Type::INT) {
                    secondVal = (float) args[1].intVal;
                } else if (args[1].type == Type::FLOAT) {
                    secondVal = args[1].floatVal;
                } else {
                    error(n, "Argument 2 not valid numberical type");
                }

                bool opresult = firstVal <= secondVal;
                stack.pushVar(line.returns[0], Variable(opresult));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }
    }
}