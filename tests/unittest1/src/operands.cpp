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
#include <polishboolfunctions/Operand.h>
#include <polishboolfunctions/Constant.h>
#include <polishboolfunctions/Variable.h>

BOOST_AUTO_TEST_SUITE(OperandsSuite)

using namespace PolishBoolFunctions;


BOOST_AUTO_TEST_CASE(ValueOfStatic)
{
    BOOST_CHECK( Constant(false).getValue() == false );
    BOOST_CHECK( Constant(true).getValue() == true );
}

BOOST_AUTO_TEST_CASE(ValueOfDynamic)
{
    std::auto_ptr<Operand> constant1(new Constant(true)),
                           var1(new Variable(7));
    BOOST_CHECK_EQUAL(static_cast<Constant*>(constant1.get())->getValue(), true);
    BOOST_CHECK_EQUAL(static_cast<Variable*>(var1.get())->getIndex(), 7);
    std::auto_ptr<Operand> var2(var1->clone());
}

BOOST_AUTO_TEST_SUITE_END()
