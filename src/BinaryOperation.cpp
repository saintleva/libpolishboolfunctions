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

#include "BinaryOperation.h"
#include <typeinfo>

using namespace PolishBoolFunctions;


/* class BinaryOperation */

BinaryOperation::~BinaryOperation() {}

BinaryOperation* BinaryOperation::clone() const
{
    return new BinaryOperation(*this);
}

AbstractOperation::Arity BinaryOperation::getArity() const
{
    return ARITY;
}

Type BinaryOperation::evaluate(const Vector& argument) const
{
    checkArgumentArity_(argument);
    return truthTable_.test( argument[0] + (argument[1] << 1) ); // this conversion it Ok
}

bool BinaryOperation::isEquivalentTo(const AbstractOperation& another) const
{
    try
    {
        const BinaryOperation& anotherBinary = dynamic_cast<const BinaryOperation&>(another);
        return anotherBinary == *this;
    }
    catch (std::bad_cast)
    {
        return false;
    }
}
