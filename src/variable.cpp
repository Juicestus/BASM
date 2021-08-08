/**
 * @file variable.cpp
 * @author Justus Languell jus@gtsbr.org
 * @brief Implemnents the Variable class
 * @version 0.1
 * @date 2021-08-08
 * 
 * @copyright Copyright (c) 2021
 */

#include "variable.h"

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
 * @param arrayv std::vector<Variable> - Array of variables
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
    Variable::type = Type::INT;
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
 * @param arrayv std::vector<Variable> - Array of variables
 */
void Variable::setArray(std::vector<Variable> arrayv) 
{
    Variable::type = Type::ARRAY;
    Variable::arrayVal = arrayv;
}
    