/**
 * @file variable.cpp
 * @author Justus Languell jus@gtsbr.org
 * @brief Implemnents the Variable class
 * @version 0.1
 * @date 2021-08-08
 * 
 * @copyright Copyright (c) 2021
 */

#include <iostream>
#include <string>
#include <vector>

#include "variable.h"
#include "error.h"

/**
 * @brief Construct a new Variable and set type to None
 */
Variable::Variable() 
{
    type = Type::NONE;
}

/**
 * @brief Construct a new Variable with value boolv and set type to Boolean
 * 
 * @param boolv bool - Boolean value
 */
Variable::Variable(bool boolv) 
{
    Variable::setBool(boolv);
}


/**
 * @brief Construct a new Variable with value intv and set type to Int
 * 
 * @param intv long int - Integer value
 */
Variable::Variable(long int intv) 
{
    Variable::setInt(intv);
}

/**
 * @brief Construct a new Variable with value floatv and set type to Float
 * 
 * @param floatv double - Floating point value
 */
Variable::Variable(double floatv) 
{
    Variable::setFloat(floatv);
}

/**
 * @brief Construct a new Variable with value strv and set type to String
 * 
 * @param strv std::string - String value
 */
Variable::Variable(std::string strv) 
{
    Variable::setString(strv);
}

/**
 * @brief Construct a new Variable with value arrayv and set type to Array 
 * 
 * @param arrayv std::vector&lt;Variable&gt; - Array of variables
 */
Variable::Variable(std::vector<Variable> arrayv) 
{
    Variable::setArray(arrayv);
}

/**
 * @brief Sets variable value to boolv and set type to Boolean
 * 
 * @param boolv bool - Boolean value
 */
void Variable::setBool(bool boolv) 
{
    Variable::type = Type::BOOL;
    Variable::boolVal = boolv;
}

/**
 * @brief Sets variable value to intv and set type to Int
 * 
 * @param intv long int - Integer value
 */
void Variable::setInt(long int intv) 
{
    Variable::type = Type::INT;
    Variable::intVal = intv;
}

/**
 * @brief Set variable value to floatv and set type to Float
 * 
 * @param floatv double - Floating point value
 */
void Variable::setFloat(double floatv) 
{
    Variable::type = Type::FLOAT;
    Variable::floatVal = floatv;
}

/**
 * @brief Set variable value to strv and set type to String
 * 
 * @param strv std::string - String value
 */
void Variable::setString(std::string strv) 
{
    Variable::type = Type::STRING;
    Variable::strVal = strv;
}

/**
 * @brief Set variable value to arrayv and set type to Array 
 * 
 * @param arrayv std::vector&lt;Variable&gt; - Array of variables
 */
void Variable::setArray(std::vector<Variable> arrayv) 
{
    Variable::type = Type::ARRAY;
    Variable::arrayVal = arrayv;
}

/**
 * @brief Set variable value to jpv and set type to Jump
 * 
 * @param jpv std::vector - Jump pointer
 */
void Variable::setJP(std::string jpv)
{
    Variable::type = Type::JUMP;
    Variable::jpVal = jpv;
}

/**
 * @brief Returns a formatted, printable representation of the variable
 * 
 * @return std::string - Printable string.
 */
std::string Variable::printable()
{
    if (Variable::type == Type::NONE) {
        return "<NoneType>";
    } else if (Variable::type == Type::BOOL) {
        return (boolVal) ? "true" : "false"; 
    } else if (Variable::type == Type::INT) {
        return std::to_string(intVal);
    } else if (Variable::type == Type::FLOAT) {
        return std::to_string(floatVal);
    } else if (Variable::type == Type::STRING) {
        return Variable::strVal;
    } else if (Variable::type == Type::ARRAY) {
        std::string out = "[ ";
        for (int i = 0; i < Variable::arrayVal.size(); i++) {
            out += Variable::arrayVal[i].printable();
            if (i < Variable::arrayVal.size() - 1) {
                out += ", ";
            } else {
                out += " ]";
            }
        }
        return out;
    } else if (Variable::type == Type::JUMP) {
        std::cout << Variable::jpVal << " (JUMP)\n";
        return "<Jump:" + Variable::jpVal + ">";
    } else {
        error(-1, "Unkown variable type in printable");
        return "";
    }
}

/**
 * @brief Prints out a repr for the varaible
 */
void Variable::repr()
{
    if (Variable::type == Type::NONE) {
        std::cout << "(NONE)" << std::endl;
    } else if (Variable::type == Type::BOOL) {
        std::cout << ((boolVal) ? "true" : "false") << " (BOOL)\n";
    } else if (Variable::type == Type::INT) {
        std::cout << Variable::intVal << " (INT)" << std::endl;
    } else if (Variable::type == Type::FLOAT) {
        printf(".3%f (FLOAT)", Variable::floatVal);
    } else if (Variable::type == Type::STRING) {
        std::cout << "\"" << Variable::strVal << "\" (STR)\n";
    } else if (Variable::type == Type::ARRAY) {
        std::cout << "[ ";
        for (Variable var : Variable::arrayVal) {
            var.repr();
            std::cout << ", ";
        }
        std::cout << "] (ARRAY)\n";
    } else if (Variable::type == Type::JUMP) {
        std::cout << Variable::jpVal << " (JUMP)\n";
    } else {
        error(-1, "Unkown variable type in repr");
    }
}
