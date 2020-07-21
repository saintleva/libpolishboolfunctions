#ifndef __LIBPOLISHBOOLFUNCTIONS_RPNFUNCTIONOPERATION_H__
#define __LIBPOLISHBOOLFUNCTIONS_RPNFUNCTIONOPERATION_H__

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
#include "RpnFunction.h"

namespace PolishBoolFunctions {


class RpnFunctionOperation: public AbstractOperation {
public:

    /* Construct/copy/destruct */

    inline explicit RpnFunctionOperation(const RpnFunction& function):
        function_(function) {}

    virtual ~RpnFunctionOperation();
    virtual RpnFunctionOperation* clone() const;

    /* Field access */

    inline RpnFunction getRpnFunction() const
    {
        return function_;
    }

    /* Use of the operation */

    virtual Arity getArity() const;

    virtual Type evaluate(const Vector& argument) const;

    /* Comparison */

    friend bool operator==(const RpnFunctionOperation& operation1, const RpnFunctionOperation& operation2);
    virtual bool isEquivalentTo(const AbstractOperation& another) const;

private:
    RpnFunction function_;

}; //class RpnFunctionOperation

inline bool operator==(const RpnFunctionOperation& operation1, const RpnFunctionOperation& operation2)
{
    return operation1.function_ == operation2.function_;
}

inline bool operator!=(const RpnFunctionOperation& operation1, const RpnFunctionOperation& operation2)
{
    return !(operation1 == operation2);
}


} //namespace PolishBoolFunctions

#endif //__LIBPOLISHBOOLFUNCTIONS_RPNFUNCTIONOPERATION_H__
