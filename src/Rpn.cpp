/*
 * Copyright (c) Anton Liaukevich 2009-2010 <leva.dev@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Rpn.h"
#include "Constant.h"
#include "Variable.h"
#include "AbstractOperation.h"
#include "exceptions.h"
#include <stack>
#include <vector>

namespace PolishBoolFunctions {


void checkCorrectnessOfRpn(const Rpn& rpn)
{
    Rpn::difference_type currentStackSize = 0;
    for (Rpn::const_iterator iter = rpn.begin(); iter != rpn.end(); ++iter)
    {
        Token* current = iter->get();
        if (dynamic_cast<Operand*>(current))
            ++currentStackSize;
        else if (const AbstractOperation* operation =
                 dynamic_cast<const AbstractOperation*>(current))
        {
            currentStackSize -= operation->getArity();
            if (currentStackSize < 0)
                throw NotEnoughArgumentsForOperation(iter);
            ++currentStackSize;
        }
        else
            throw TokenIsNeitherOperandNorOperation(current);
    }
    if (currentStackSize != 1)
        throw NotExactlyOneEvaluationResult(currentStackSize);
}

template<> Type evaluateRpn<DontCheck>(const Rpn& rpn, const ArgumentList& arguments)
{
    std::stack<Type,std::vector<Type> > stack;

    for (Rpn::const_iterator iter = rpn.begin(); iter != rpn.end(); ++iter)
        if (const Constant* constant = dynamic_cast<const Constant*>(iter->get()))
            stack.push(constant->getValue());
        else if (const Variable* variable = dynamic_cast<const Variable*>(iter->get()))
        {
            Variable::Index index = variable->getIndex();
            if (index < arguments.size())
                stack.push(arguments[index]);
            else
                throw VariableIndexOutOfArgListBounds(index, arguments.size());
        }
        else if (const AbstractOperation* operation =
                 dynamic_cast<const AbstractOperation*>(iter->get()))
        {
            Rpn::difference_type arity = operation->getArity();
            AbstractOperation::Vector argument(arity);
            while (arity > 0)
            {
                --arity;
                argument[arity] = stack.top();
                stack.pop();
            }
            stack.push(operation->evaluate(argument));
        }
    return stack.top();
}

template<> Type evaluateRpn<DoCheck>(const Rpn& rpn, const ArgumentList& arguments)
{
    std::stack<Type,std::vector<Type> > stack;

    for (Rpn::const_iterator iter = rpn.begin(); iter != rpn.end(); ++iter)
    {
        Token* current = iter->get();
        if (const Constant* constant = dynamic_cast<const Constant*>(iter->get()))
            stack.push(constant->getValue());
        else if (const Variable* variable = dynamic_cast<const Variable*>(iter->get()))
        {
            Variable::Index index = variable->getIndex();
            if (index < arguments.size())
                stack.push(arguments[index]);
            else
                throw VariableIndexOutOfArgListBounds(index, arguments.size());
        }
        else if (const AbstractOperation* operation =
                 dynamic_cast<const AbstractOperation*>(current))
        {
            Rpn::size_type arity = operation->getArity();
            if (stack.size() < arity)
                throw NotEnoughArgumentsForOperation(iter);

            AbstractOperation::Vector argument(arity);
            while (arity > 0)
            {
                --arity;
                argument[arity] = stack.top();
                stack.pop();
            }
            stack.push(operation->evaluate(argument));
        }
        else
            throw TokenIsNeitherOperandNorOperation(current);
    }
    if (stack.size() == 1)
        return stack.top();
    else
        throw NotExactlyOneEvaluationResult(stack.size());
}


} //namespace PolishBoolFunctions
