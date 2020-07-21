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

#include "RpnFunctionOperation.h"
#include "Rpn.h"
#include <typeinfo>

using namespace PolishBoolFunctions;


/* class RpnFunctionOperation */

RpnFunctionOperation::~RpnFunctionOperation() {}

RpnFunctionOperation* RpnFunctionOperation::clone() const
{
    return new RpnFunctionOperation(*this);
}

AbstractOperation::Arity RpnFunctionOperation::getArity() const
{
    return function_.arity;
}

Type RpnFunctionOperation::evaluate(const Vector& argument) const
{
    checkArgumentArity_(argument);
    return evaluateRpn<DontCheck>(*function_.rpn, argument);
}

bool RpnFunctionOperation::isEquivalentTo(const AbstractOperation& another) const
{
    try
    {
        const RpnFunctionOperation& anotherFunc = dynamic_cast<const RpnFunctionOperation&>(another);
        return anotherFunc == *this;
    }
    catch (std::bad_cast)
    {
        return false;
    }
}
