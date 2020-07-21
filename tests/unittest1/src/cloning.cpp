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

#include <memory>
#include <boost/test/unit_test.hpp>
#include <polishboolfunctions/exceptions.h>
#include <polishboolfunctions/Variable.h>
#include <polishboolfunctions/BinaryOperation.h>
#include <polishboolfunctions/NotOperation.h>


BOOST_AUTO_TEST_SUITE(CloningSuite)

using namespace PolishBoolFunctions;


BOOST_AUTO_TEST_CASE(StaticTypeSaving)
{
    Variable var1(5);
    std::auto_ptr<Variable> var2(var1.clone());
    BOOST_CHECK_EQUAL(var2->getIndex(), 5);
}

BOOST_AUTO_TEST_CASE(Operations)
{
    for (unsigned long opCode = 0x0ul; opCode < 0x10ul; ++opCode)
    {
        typedef BinaryOperation::TruthTable Table;

        std::auto_ptr<BinaryOperation> op1(new BinaryOperation(Table(opCode)));
        AbstractOperation* current = op1->clone();
        BOOST_CHECK( current->isEquivalentTo(*op1) );
        delete current;
    }

    std::auto_ptr<NotOperation> notCopy(NotOperation().clone());
    BOOST_CHECK( notCopy->isEquivalentTo(UnaryOperators::Not) );
}


BOOST_AUTO_TEST_SUITE_END()
