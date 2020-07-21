#ifndef __LIBPOLISHBOOLFUNCTIONS_VARIABLE_H__
#define __LIBPOLISHBOOLFUNCTIONS_VARIABLE_H__

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
#include "ArgumentList.h"
#include "exceptions.h"

namespace PolishBoolFunctions {


/**
 * Class for all variables that may be present at the RPN. This is final class and user must
 * use exactly it. This class has not getValue() method because it stores (and can return) only
 * index.
 * @author Anton Liaukevich
 */
class Variable: public Operand {
public:

    /* Types */

    typedef ArgumentList::size_type Index;

    /* Construct/copy/destruct */

    inline explicit Variable(Index index):
        index_(index) {}

    virtual ~Variable();
    virtual Variable* clone() const;

    /* Value access */

    inline Index getIndex() const
    {
        return index_;
    }

private:

    Index index_;

}; //class Variable


} //namespace PolishBoolFunctions

#endif // __LIBPOLISHBOOLFUNCTIONS_VARIABLE_H__
