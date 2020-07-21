#ifndef __LIBPOLISHBOOLFUNCTIONS_CONSTANT_H__
#define __LIBPOLISHBOOLFUNCTIONS_CONSTANT_H__

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

#include "Operand.h"

namespace PolishBoolFunctions {


/**
 * Constants that may be present at the RPN. Simply stores a boolean value.
 * @author Anton Liaukevich
 */
class Constant: public Operand {
public:
    /* Construct/copy/destruct */

    inline explicit Constant(Type value):
        value_(value) {}

    virtual ~Constant();
    virtual Constant* clone() const;

    /* Accessors */

    /**
     * Returns the value of the constant
     */
    inline Type getValue() const
    {
        return value_;
    };

private:
    Type value_;

}; //class Constant


} //namespace PolishBoolFunctions

#endif // __LIBPOLISHBOOLFUNCTIONS_CONSTANT_H__
