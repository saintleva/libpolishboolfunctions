#ifndef __LIBPOLISHBOOLFUNCTIONS_NOTOPERATION_H__
#define __LIBPOLISHBOOLFUNCTIONS_NOTOPERATION_H__

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

#include "AbstractOperation.h"

namespace PolishBoolFunctions {


/**
 * NOT operation. Doesn't store anything. All instances of this class are equivalent.
 * @author Anton Liaukevich
 */
struct NotOperation: public AbstractOperation {

    /* Compile-time constants */
    enum { ARITY = 1 };

    /* Construct/copy/destruct */
    inline NotOperation() {}
    virtual ~NotOperation();
    virtual NotOperation* clone() const;

    /* Use of operation */
    virtual Arity getArity() const;
    virtual Type evaluate(const Vector& argument) const;

    /* Comparison */
    virtual bool isEquivalentTo(const AbstractOperation& another) const;

}; //struct NotOperation

/**
 * Defines some unary operations
 * @author Anton Liaukevich
 */
namespace UnaryOperators {

    const NotOperation Not;

} //namespace UnaryOperators


} //namespace PolishBoolFunctions


#endif //__LIBPOLISHBOOLFUNCTIONS_NOTOPERATION_H__
