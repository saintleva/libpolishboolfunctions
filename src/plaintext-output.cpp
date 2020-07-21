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

#include "plaintext-output.h"
#include "NotOperation.h"
#include "BinaryOperation.h"
#include "exceptions.h"

using namespace PolishBoolFunctions::PlaintextIO;


std::string TextualOperationSymbols::symbol(const AbstractOperation* operation)
{
    using namespace UnaryOperators;
    using namespace BinaryOperators;

    if (operation->isEquivalentTo(Not))
        return "Not";
    else if (operation->isEquivalentTo(BinaryOperators::IdenticalFalse))
        return "BinaryIdenticalFalse";
    else if (operation->isEquivalentTo(NotOr))
        return "NotOr";
    else if (operation->isEquivalentTo(Greater))
        return "AndNot";
    else if (operation->isEquivalentTo(NotSecond))
        return "NotSecond";
    else if (operation->isEquivalentTo(Less))
	    return "Less";
    else if (operation->isEquivalentTo(NotFirst))
        return "NotFirst";
    else if (operation->isEquivalentTo(Xor))
        return "Xor";
    else if (operation->isEquivalentTo(NotAnd))
        return "NotAnd";
    else if (operation->isEquivalentTo(And))
        return "And";
    else if (operation->isEquivalentTo(Equal))
        return "Equal";
    else if (operation->isEquivalentTo(First))
        return "First";
    else if (operation->isEquivalentTo(ReverseImplies))
        return "ReverseImplies";
    else if (operation->isEquivalentTo(Second))
        return "Second";
    else if (operation->isEquivalentTo(Implies))
        return "Implies";
    else if (operation->isEquivalentTo(Or))
        return "Or";
    else if (operation->isEquivalentTo(BinaryOperators::IdenticalTrue))
        return "BinaryIdenticalTrue";
    else
        throw OperationIsUnknown(operation);
}
