/**
 * @file eval.h
 * @author Justus Languell (jus@gtsbr.org)
 * @brief Header for evaluation functions.
 * @version 0.4
 * @date 2021-08-09
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef EVAL_H_
#define EVAL_H_

#include <string>
#include <vector>
#include <cmath>

#include "parse.h"
#include "error.h"
#include "variable.h"
#include "stack.h"

/**
 * @brief Evaluates the expression.
 * 
 * @param stack Stack - The memory stack object.
 * @param lines std::vector&lt;Line&gt; - The parse expression lines.
 */
void evaluate(Stack stack, std::vector<Line> linse);

#endif