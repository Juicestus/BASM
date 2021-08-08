/**
 * @file Variableiable.h
 * @author Justus Languell jus@gtsbr.org
 * @brief 
 * @version 0.1
 * @date 2021-08-08
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef Variable_H_
#define Variable_H_

#include <string>
#include <vector>

namespace Type 
{
    const int NONE = 0;
    const int INT = 1;
    const int FLOAT = 2;
    const int STRING = 3;
    const int ARRAY = 4;
}

class Variable
{
private:
    int type;

    long int intVal;
    double floatVal;
    std::string strVal;
    std::vector<Variable> arrayVal;

public:
    Variable();
    Variable(long int intv);
    Variable(double flaotv);
    Variable(std::string strv);
    Variable(std::vector<Variable> arrayv);

    void setInt(long int intVal);
    void setFloat(double floatVal);
    void setString(std::string strVal);
    void setArray(std::vector<Variable> arrayVal);
};

#endif