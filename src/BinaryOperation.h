#ifndef __LIBPOLISHBOOLFUNCTIONS_BINARYOPERATION_H__
#define __LIBPOLISHBOOLFUNCTIONS_BINARYOPERATION_H__

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
#include <bitset>

namespace PolishBoolFunctions {


/**
 * Binary operation. An instances of it simply store truth table for a binary boolean function.
 * @author Anton Liaukevich
 */
class BinaryOperation: public AbstractOperation {
public:

    /* Types and compile-time constants */

    enum { ARITY = 2 };
    typedef std::bitset<4> TruthTable;

    /* Construct/copy/destruct */

    inline explicit BinaryOperation(TruthTable truthTable):
        truthTable_(truthTable) {}

    virtual ~BinaryOperation();
    virtual BinaryOperation* clone() const;

    /* Accessor */

    inline TruthTable getTruthTable() const
    {
        return truthTable_;
    }

    /* Use of operation */

    virtual Arity getArity() const;
    virtual Type evaluate(const Vector& argument) const;

    /* Comparison */

    friend bool operator==(const BinaryOperation& operation1, const BinaryOperation& operation2);
    virtual bool isEquivalentTo(const AbstractOperation& another) const;

private:
    TruthTable truthTable_;

}; //class BinaryOperation

/**
 * Defines every possible (16) binary boolean functions defined by their generally accepted names
 * (and aliases for certain of them).
 * @author Anton Liaukevich
 */
namespace BinaryOperators {

    typedef BinaryOperation::TruthTable Table;

    const BinaryOperation IdenticalFalse(Table(0x0ul)),
                          NotOr         (Table(0x1ul)),
                          Greater       (Table(0x2ul)),
                          NotSecond     (Table(0x3ul)),
                          Less          (Table(0x4ul)),
                          NotFirst      (Table(0x5ul)),
                          Xor           (Table(0x6ul)),
                          NotAnd        (Table(0x7ul)),
                          And           (Table(0x8ul)),
                          Equal         (Table(0x9ul)),
                          First         (Table(0xAul)),
                          ReverseImplies(Table(0xBul)),
                          Second        (Table(0xCul)),
                          Implies       (Table(0xDul)),
                          Or            (Table(0xEul)),
                          IdenticalTrue (Table(0xFul));

    const BinaryOperation AndNot         = Greater,
                          GreaterOrEqual = ReverseImplies,
                          LessOrEqual    = Implies;

} //namespace BinaryOperators

inline bool operator==(const BinaryOperation& operation1, const BinaryOperation& operation2)
{
    return operation1.truthTable_ == operation2.truthTable_;
}

inline bool operator!=(const BinaryOperation& operation1, const BinaryOperation& operation2)
{
    return !(operation1 == operation2);
}


} //namespace PolishBoolFunctions


#endif //__LIBPOLISHBOOLFUNCTIONS_BINARYOPERATION_H__
