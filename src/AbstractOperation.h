#ifndef __LIBPOLISHBOOLFUNCTIONS_ABSTRACTOPERATION_H__
#define __LIBPOLISHBOOLFUNCTIONS_ABSTRACTOPERATION_H__

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

#include "types.h"
#include "Token.h"
#include "ArgumentList.h"
#include <vector>

namespace PolishBoolFunctions {


/**
 * Base (abstract) class for all operations (of arbitrary arity) that may be present at the RPN
 * @author Anton Liaukevich
 */
class AbstractOperation: public Token {
public:

    /* Types */

    /**
     * A boolean vector (of arbitrary size)
     */
    typedef ArgumentList Vector;

    typedef Vector::size_type Arity;

    /* Construct/copy/destruct */

    virtual ~AbstractOperation();
    virtual AbstractOperation* clone() const = 0;

    /* Use of the operation */

    virtual Arity getArity() const = 0;

    /**
     * Evaluates the operation on concrete vector-argument
     * @return Result of the operation
     * @throw ArgumentDoesntAgreeWithArity if argument.size() != getArity()
     */
    virtual Type evaluate(const Vector& argument) const = 0;

    /* Comparison */

    /**
     * Checks if this operation is equivalent to another.
     * @return true if operations have equal arity and they are equivalent, otherwise false.
     */
    virtual bool isEquivalentTo(const AbstractOperation& another) const = 0;

protected:

    void checkArgumentArity_(const Vector& argument) const;

}; //class AbstractOperation


} //namespace PolishBoolFunctions


#endif //__LIBPOLISHBOOLFUNCTIONS_ABSTRACTOPERATION_H__
