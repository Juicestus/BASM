/**
 * @file Variableiable.h
 * @author Justus Languell jus@gtsbr.org
 * @brief Defines the type namespace and variable class
 * @version 0.1
 * @date 2021-08-08
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef Variable_H_
#define Variable_H_

#include <iostream>
#include <string>
#include <vector>

#include "variable.h"

namespace Type 
{
    const int NONE = 0;
    const int BOOL = 1;
    const int INT = 2;
    const int FLOAT = 3;
    const int STRING = 4;
    const int ARRAY = 5;
    const int JUMP = 6;
}

/**
 * @brief Variable class
 * @note Method comments are in implementation file.
 */
class Variable
{
public:

    int type;

    bool boolVal;
    long int intVal;
    double floatVal;
    std::string strVal;
    std::vector<Variable> arrayVal;
    std::string jpVal;

    Variable();
    Variable(bool boolv);
    Variable(long int intv);
    Variable(double flaotv);
    Variable(std::string strv);
    Variable(std::vector<Variable> arrayv);

    void setBool(bool boolv);
    void setInt(long int intv);
    void setFloat(double floatv);
    void setString(std::string strv);
    void setArray(std::vector<Variable> arrayv);
    void setJP(std::string jpv);

    void repr();
};

#endif