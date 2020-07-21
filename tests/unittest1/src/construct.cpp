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

#include <boost/test/unit_test.hpp>
#include <polishboolfunctions/exceptions.h>
#include <polishboolfunctions/Constant.h>
#include <polishboolfunctions/BinaryOperation.h>
#include <polishboolfunctions/NotOperation.h>

BOOST_AUTO_TEST_SUITE(ConstructSuite)

using namespace PolishBoolFunctions;


BOOST_AUTO_TEST_CASE(Constants)
{
    Constant constant1(true);
    Constant constant2 = constant1,
             constant3(constant2);
    Constant constant4(false);
    constant4 = constant1;

    BOOST_CHECK( constant1.getValue() == true &&
                 constant2.getValue() == true &&
                 constant3.getValue() == true &&
                 constant4.getValue() == true );
}

AbstractOperation::Vector alone(Type x0)
{
    return AbstractOperation::Vector(1, x0);
}

AbstractOperation::Vector pair(Type x0, Type x1)
{
    AbstractOperation::Vector result(2);
    result[0] = x0;
    result[1] = x1;
    return result;
}

BOOST_AUTO_TEST_CASE(SomeReadyOperators)
{
    using namespace UnaryOperators;
    using namespace BinaryOperators;

    BOOST_CHECK_EQUAL(Not.getArity(), 1);
    BOOST_CHECK_EQUAL(And.getArity(), 2);

    BOOST_CHECK_THROW(And.evaluate(AbstractOperation::Vector(0)), ArgumentDoesntAgreeWithArity);
    BOOST_CHECK_THROW(And.evaluate(AbstractOperation::Vector(10)), ArgumentDoesntAgreeWithArity);
    BOOST_CHECK_THROW(And.evaluate(alone(false)), ArgumentDoesntAgreeWithArity);
    BOOST_CHECK_THROW(Not.evaluate(pair(false, true)), ArgumentDoesntAgreeWithArity);

    BOOST_CHECK_EQUAL(And.evaluate(pair(false, false)), false);
    BOOST_CHECK_EQUAL(And.evaluate(pair(true,  false)), false);
    BOOST_CHECK_EQUAL(And.evaluate(pair(false, true)),  false);
    BOOST_CHECK_EQUAL(And.evaluate(pair(true,  true)),  true);

    BOOST_CHECK_EQUAL(Or.evaluate(pair(false, false)), false);
    BOOST_CHECK_EQUAL(Or.evaluate(pair(true,  false)), true);
    BOOST_CHECK_EQUAL(Or.evaluate(pair(false, true)),  true);
    BOOST_CHECK_EQUAL(Or.evaluate(pair(true,  true)),  true);

    BOOST_CHECK_EQUAL(Xor.evaluate(pair(false, false)), false);
    BOOST_CHECK_EQUAL(Xor.evaluate(pair(true,  false)), true);
    BOOST_CHECK_EQUAL(Xor.evaluate(pair(false, true)),  true);
    BOOST_CHECK_EQUAL(Xor.evaluate(pair(true,  true)),  false);

    BOOST_CHECK_EQUAL(Not.evaluate(alone(false)), true);
    BOOST_CHECK_EQUAL(Not.evaluate(alone(true)),  false);

    BOOST_CHECK_EQUAL(AndNot.evaluate(pair(false, false)), false);
    BOOST_CHECK_EQUAL(AndNot.evaluate(pair(true,  false)), true);
    BOOST_CHECK_EQUAL(AndNot.evaluate(pair(false, true)),  false);
    BOOST_CHECK_EQUAL(AndNot.evaluate(pair(true,  true)),  false);

    BOOST_CHECK( AndNot == Greater );
    BOOST_CHECK( And != Xor );

    BOOST_CHECK( Not.isEquivalentTo(Not) );
    BOOST_CHECK( AndNot.isEquivalentTo(AndNot) );
    BOOST_CHECK( AndNot.isEquivalentTo(Greater) );
    BOOST_CHECK( !And.isEquivalentTo(Xor) );
    BOOST_CHECK( !And.isEquivalentTo(Not) );
}


BOOST_AUTO_TEST_SUITE_END()
