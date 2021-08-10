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
#include <cmath>

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

        if (line.command == "") 
        {
            error(n, "No command given");
        }

        /* FLOW CONTROL */

        /**
         * @brief Jump function
         * Takes in two args, boolean to jump or not, and 
         * goto pointer. Jumps to the goto pointer.
         */
        else if (line.command == "jump") 
        {
            if (args[0].type == Type::BOOL
                && args[1].type == Type::JUMP) {
                if (args[0].boolVal) {
                    n = pointers[args[1].jpVal] - 1;
                }
            } else {
                error(n, "Either non valid boolean or jump/goto pointer");
            }
        }

        /* INPUT/OUTPUT */

         /**
         * @brief print function
         * Prints all args in sequence with no break
         */
        else if (line.command == "print") 
        {
            std::string output = "";
            for (int i=0; i < args.size(); i++) {
                output += args[i].printable();
            }
            std::cout << output;
        }

        /**
         * @brief read function
         * Reads a string from terminal
         */
        else if (line.command == "read")
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            std::string input;
            std::cin >> input;

            if (args.size() == 1) {
                stack.pushVar(line.returns[0], Variable(input));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }


        /* VARIABLE/CONVERSION OPS */

        /**
         * @brief isnul function
         * Returns a bool for if the only argument is a boolean
         */
        else if (line.command == "isnul") {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 1) {
                stack.pushVar(line.returns[0], Variable(args[0].type == Type::NONE));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }

        /**
         * @brief type function
         * Returns a int for if the type of the only argument
         */
        else if (line.command == "type") {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 1) {
                stack.pushVar(line.returns[0], Variable((long) args[0].type));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }

        /**
         * @brief stoi function
         * Converts string to integer if sucsessful
         * otherwise returns NONE
         */
        else if (line.command == "stoi") {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 1) {
                std::string strval;

                if (args[0].type == Type::STRING) {
                    strval = args[0].strVal;
                } else {
                    error(n, "Argument 1 not valid string type");
                }

                try {
                    stack.pushVar(line.returns[0], Variable((long) std::stoi(strval)));
                } catch (...) {
                    stack.pushVar(line.returns[0], Variable());
                    //error(n, "Argument 1 not valid integer");
                }
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }

        /**
         * @brief stof function
         * Converts string to float if sucsessful
         * otherwise returns NONE
         */
        else if (line.command == "stof") {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 1) {
                std::string strval;

                if (args[0].type == Type::STRING) {
                    strval = args[0].strVal;
                } else {
                    error(n, "Argument 1 not valid string type");
                }

                try {
                    stack.pushVar(line.returns[0], Variable(std::stof(strval)));
                } catch (...) {
                    stack.pushVar(line.returns[0], Variable());
                    //error(n, "Argument 1 not valid integer");
                }
            } else {
                error(n, "Invalid ammount of arguments");
            }
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
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            stack.pushVar(line.returns[0], args[0]);
        }


        /* ARITHMETIC OPS */

        /**
         * @brief Addition function
         * Takes in n args of type int or float
         * Returns int or float sum of args
         */
        else if (line.command == "sum") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

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
         * @brief Addition function
         * Adds two numbers
         */
        else if (line.command == "add") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 2) {
                Variable one = args[0];
                Variable two = args[1];

                bool isFloat = (one.type == Type::FLOAT 
                                || two.type == Type::FLOAT);

                if (one.type != Type::INT && one.type != Type::FLOAT) {
                    error(n, "First Addition argument invalid type!");
                }
                if (two.type != Type::INT && two.type != Type::FLOAT) {
                    error(n, "Second Addition argument invalid type!");
                }

                if (isFloat) {
                    stack.pushVar(line.returns[0], Variable(one.floatVal + two.floatVal));
                } else {
                    stack.pushVar(line.returns[0], Variable(one.intVal + two.intVal));
                }
            }
        }

        /**
         * @brief Subtraction function
         * Subtracts n2 from n1, sometimes
         * better off adding negatives
         */
        else if (line.command == "sub") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 2) {
                Variable one = args[0];
                Variable two = args[1];

                bool isFloat = (one.type == Type::FLOAT 
                                || two.type == Type::FLOAT);

                if (one.type != Type::INT && one.type != Type::FLOAT) {
                    error(n, "First Subtraction argument invalid type!");
                }
                if (two.type != Type::INT && two.type != Type::FLOAT) {
                    error(n, "Second Subtraction argument invalid type!");
                }

                if (isFloat) {
                    stack.pushVar(line.returns[0], Variable(one.floatVal - two.floatVal));
                } else {
                    stack.pushVar(line.returns[0], Variable(one.intVal - two.intVal));
                }
            }
        }

        /**
         * @brief Mutliplication function
         * Multiplies two numbers
         */
        else if (line.command == "mult") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            Variable one = args[0];
            Variable two = args[1];

            bool isFloat = (one.type == Type::FLOAT 
                            || two.type == Type::FLOAT);

            if (one.type != Type::INT && one.type != Type::FLOAT) {
                error(n, "First Mutliplication argument invalid type!");
            }
            if (two.type != Type::INT && two.type != Type::FLOAT) {
                error(n, "Second Mutliplication argument invalid type!");
            }

            if (isFloat) {
                stack.pushVar(line.returns[0], Variable(one.floatVal * two.floatVal));
            } else {
                stack.pushVar(line.returns[0], Variable(one.intVal * two.intVal));
            }
        }

         /**
         * @brief Division function
         * Divides n1 by n2
         * 
         * Generaly always returns float but I
         * didn't want to change the template.
         * 
         */
        else if (line.command == "div") 
        {
            if (args.size() == 2) {
                Variable one = args[0];
                Variable two = args[1];

                bool isFloat = (one.type == Type::FLOAT 
                                || two.type == Type::FLOAT);

                if (one.type != Type::INT && one.type != Type::FLOAT) {
                    error(n, "First Division argument invalid type!");
                }
                if (two.type != Type::INT && two.type != Type::FLOAT) {
                    error(n, "Second Division argument invalid type!");
                }

                if (isFloat) {
                    stack.pushVar(line.returns[0], Variable(one.floatVal / two.floatVal));
                } else {
                    stack.pushVar(line.returns[0], Variable(one.intVal / two.intVal));
                }
            }
        }


        /**
         * @brief Modulo function
         * n1 modulo n2
         */
        else if (line.command == "mod") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 2) {
                Variable one = args[0];
                Variable two = args[1];

                bool isFloat = (one.type == Type::FLOAT 
                                || two.type == Type::FLOAT);

                if (one.type != Type::INT && one.type != Type::FLOAT) {
                    error(n, "First Modulo argument invalid type!");
                }
                if (two.type != Type::INT && two.type != Type::FLOAT) {
                    error(n, "Second Modulo argument invalid type!");
                }

                if (isFloat) {
                    stack.pushVar(line.returns[0], Variable(fmod(one.floatVal, two.floatVal)));
                } else {
                    stack.pushVar(line.returns[0], Variable(one.intVal % two.intVal));
                }
            }
        }

        /**
         * @brief Power function
         * n1 raised to the n2-th power
         */
        else if (line.command == "pow") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 2) {
                Variable one = args[0];
                Variable two = args[1];

                bool isFloat = (one.type == Type::FLOAT 
                                || two.type == Type::FLOAT);

                if (one.type != Type::INT && one.type != Type::FLOAT) {
                    error(n, "First Power argument invalid type!");
                }
                if (two.type != Type::INT && two.type != Type::FLOAT) {
                    error(n, "Second Power argument invalid type!");
                }

                if (isFloat) {
                    stack.pushVar(line.returns[0], Variable(pow(one.floatVal, two.floatVal)));
                } else {
                    stack.pushVar(line.returns[0], Variable(pow(one.intVal, two.intVal)));
                }
            }
        }

        /* BOOLEAN OPS */

        /**
         * @brief not function
         * Returns not of only parameter
         */
        else if (line.command == "not") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 1) {
                bool val;

                if (args[0].type == Type::BOOL) {
                    val = args[0].boolVal;
                } else {
                    error(n, "Argument 1 not valid numberical type");
                }

                stack.pushVar(line.returns[0], Variable(!val));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }

        /**
         * @brief or function
         * Returns not of only parameter
         */
        else if (line.command == "or") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 2) {
                bool val1;
                bool val2;

                if (args[0].type == Type::BOOL) {
                    val1 = args[0].boolVal;
                } else {
                    error(n, "Argument 1 not valid numberical type");
                }

                if (args[0].type == Type::BOOL) {
                    val2 = args[0].boolVal;
                } else {
                    error(n, "Argument 2 not valid numberical type");
                }

                stack.pushVar(line.returns[0], Variable(val1 || val2));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }

        /**
         * @brief or function
         * Returns not of only parameter
         */
        else if (line.command == "and") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 2) {
                bool val1;
                bool val2;

                if (args[0].type == Type::BOOL) {
                    val1 = args[0].boolVal;
                } else {
                    error(n, "Argument 1 not valid numberical type");
                }

                if (args[0].type == Type::BOOL) {
                    val2 = args[0].boolVal;
                } else {
                    error(n, "Argument 2 not valid numberical type");
                }

                stack.pushVar(line.returns[0], Variable(val1 && val2));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }

        /* COMPARISON OPS */

        /**
         * @brief eq function
         * Sets only return bool to the less than operation
         * between the first two args, ints or floats.
         */
        else if (line.command == "eq") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

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

                bool opresult = firstVal == secondVal;
                stack.pushVar(line.returns[0], Variable(opresult));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }

        /**
         * @brief lt function
         * Sets only return bool to the less than operation
         * between the first two args, ints or floats.
         */
        else if (line.command == "lt") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

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

                bool opresult = firstVal < secondVal;
                stack.pushVar(line.returns[0], Variable(opresult));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }

        /**
         * @brief gt function
         * Sets only return bool to the greater than operation
         * between the first two args, ints or floats.
         */
        else if (line.command == "gt") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

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

                bool opresult = firstVal > secondVal;
                stack.pushVar(line.returns[0], Variable(opresult));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }

        /**
         * @brief lteq function
         * Sets only return bool to the less than or equal operation
         * between the first two args, ints or floats.
         */
        else if (line.command == "lteq") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

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

        /**
         * @brief gteq function
         * Sets only return bool to the greater than or equal operation
         * between the first two args, ints or floats.
         */
        else if (line.command == "gteq") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

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

                bool opresult = firstVal >= secondVal;
                stack.pushVar(line.returns[0], Variable(opresult));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }

        /* STRING OPS */
        /**
         * @brief eq function
         * Sets only return bool to the less than operation
         * between the first two args, ints or floats.
         */
        else if (line.command == "streq") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 2) {
                std::string firstVal;
                std::string secondVal;

                if (args[0].type == Type::STRING) {
                    firstVal = args[0].strVal;
                } else {
                    error(n, "Argument 1 not valid string type");
                }

                if (args[1].type == Type::STRING) {
                    secondVal = args[1].strVal;
                } else {
                    error(n, "Argument 2 not valid string type");
                }

                bool opresult = firstVal == secondVal;
                stack.pushVar(line.returns[0], Variable(opresult));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }

        else if (line.command == "charat") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            if (args.size() == 2) {
                std::string firstVal;
                int secondVal;

                if (args[0].type == Type::STRING) {
                    firstVal = args[0].strVal;
                } else {
                    error(n, "Argument 1 not valid string type");
                }

                if (args[1].type == Type::INT) {
                    secondVal = args[1].intVal;
                } else {
                    error(n, "Argument 2 not valid int type");
                }

                stack.pushVar(line.returns[0], Variable(
                    std::to_string(firstVal[secondVal])));
            } else {
                error(n, "Invalid ammount of arguments");
            }
        }


        /**
         * @brief Cat function
         * Takes in n args of any type and outputs
         * a string concatenation of the args.
         * 
         * The default "to string" function kinda
         * No need for another conversion
         */
        else if (line.command == "cat") 
        {
            if (line.returns.size() == 0) {
                error(n, "Invalid ammount of returns");
            }

            std::string result;
            for (int i=0; i < args.size(); i++) {
                result += args[i].printable();
            }
            stack.pushVar(line.returns[0], Variable(result));
        }



    }
}