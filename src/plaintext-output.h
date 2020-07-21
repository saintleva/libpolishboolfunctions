#ifndef __LIBPOLISHBOOLFUNCTIONS_PLAINTEXTOUTPUT_H__
#define __LIBPOLISHBOOLFUNCTIONS_PLAINTEXTOUTPUT_H__

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
#include "Token.h"
#include "Constant.h"
#include "Variable.h"
#include "AbstractOperation.h"
#include <string>
#include <ostream>
#include <boost/format.hpp>

namespace PolishBoolFunctions { namespace PlaintextIO {


struct TextualOperationSymbols {

    static std::string symbol(const AbstractOperation* operation);

}; //struct TextualOperationSymbols

template<class OperationSymbols>
struct TokenOutputPolicy {

    inline static std::string tokenToStr(const Token* token)
    {
        if (const Constant* constant = dynamic_cast<const Constant*>(token))
            return constant->getValue() ? "1" : "0";
        else if (const Variable* variable = dynamic_cast<const Variable*>(token))
            return (boost::format("x_%1%") % variable->getIndex()).str();
        else if (const AbstractOperation* operation = dynamic_cast<const AbstractOperation*>(token))
            return OperationSymbols::symbol(operation);
    }

}; //struct TokenOutputPolicy

class SimpleHorizontalOutputer {
public:

    SimpleHorizontalOutputer(std::ostream& output, Rpn::size_type size):
        output_(output), size_(size) {};

    inline void start() {}
    inline void finish() {}

    inline void add(const std::string& current)
    {
        output_ << current;
        --size_;
        if (size_ > 0)
            output_ << " ";
    }

private:
    std::ostream& output_;
    Rpn::size_type size_;

}; //class SimpleHorizontalStructure

class SimpleVerticalOutputer {
public:

    SimpleVerticalOutputer(std::ostream& output, Rpn::size_type):
        output_(output) {};

    inline void start() {}
    inline void finish() {}

    inline void add(const std::string& current)
    {
        output_ << current << "\n";
    }

private:
    std::ostream& output_;

}; //class SimpleVerticalOutputer


}} //namespace PolishBoolFunctions::PlaintextIO

#endif //__LIBPOLISHBOOLFUNCTIONS_PLAINTEXTOUTPUT_H__
