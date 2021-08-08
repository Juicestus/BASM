/**
 * @file variable.cpp
 * @author Justus Languell jus@gtsbr.org
 * @brief 
 * @version 0.1
 * @date 2021-08-08
 * 
 * @copyright Copyright (c) 2021
 */

#include "variable.h"

const int Type::NONE = 0;
const int Type::INT = 1;
const int Type::FLOAT = 2;
const int Type::STRING = 3;
const int Type::ARRAY = 4;

Variable::Variable() 
{
    type = Type::NONE;
}

Variable::Variable(long int intv) 
{
    Variable::setInt(intv);
}

Variable::Variable(double floatv) 
{
    Variable::setFloat(floatv);
}

Variable::Variable(std::string strv) 
{
    Variable::setString(strv);
}

Variable::Variable(std::vector<Variable> arrayv) 
{
    Variable::setArray(arrayv);
}

void Variable::setInt(long int intv) 
{
    Variable::type = Type::INT;
    Variable::intVal = intv;
}

void Variable::setFloat(double floatv) 
{
    Variable::type = Type::FLOAT;
    Variable::floatVal = floatv;
}

void Variable::setString(std::string strv) 
{
    Variable::type = Type::STRING;
    Variable::strVal = strv;
}

void Variable::setArray(std::vector<Variable> arrayv) 
{
    Variable::type = Type::ARRAY;
    Variable::arrayVal = arrayv;
}
    