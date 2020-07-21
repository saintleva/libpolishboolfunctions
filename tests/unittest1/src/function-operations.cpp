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
#include <polishboolfunctions/Constant.h>
#include <polishboolfunctions/ArgumentList.h>
#include <polishboolfunctions/Variable.h>
#include <polishboolfunctions/BinaryOperation.h>
#include <polishboolfunctions/NotOperation.h>
#include <polishboolfunctions/Rpn.h>
#include <polishboolfunctions/RpnFunctionOperation.h>
#include <polishboolfunctions/exceptions.h>

BOOST_AUTO_TEST_SUITE(FunctionOperationsSuite)

using namespace PolishBoolFunctions;


BOOST_AUTO_TEST_CASE(Case1)
{
    Type initialValues[10] = { true, true, false, true, false, true, true, true, false, true };
    ArgumentList args1(initialValues, initialValues + 10);

    Rpn func1;
    for (Variable::Index i = 0; i < 10; ++i)
        func1.push_back(TokenPtr(new Variable(i)));
    for (Rpn::size_type i = 0; i < 8; ++i)
        func1.push_back(TokenPtr(BinaryOperators::Xor.clone()));
    BOOST_CHECK_THROW(checkCorrectnessOfRpn(func1), NotExactlyOneEvaluationResult);

    BOOST_CHECK_THROW(evaluateRpn<DoCheck>(func1, args1), NotExactlyOneEvaluationResult);

    func1.push_back(TokenPtr(BinaryOperators::And.clone()));
    BOOST_CHECK_NO_THROW(checkCorrectnessOfRpn(func1));

    BOOST_CHECK_EQUAL( evaluateRpn<DoCheck>(func1, args1), false );
    BOOST_CHECK_EQUAL( evaluateRpn<DontCheck>(func1, args1), false );

    AbstractOperation* func1Operation = new RpnFunctionOperation(RpnFunction(&func1, 10));
    BOOST_CHECK_EQUAL( func1Operation->evaluate(args1), false );
    delete func1Operation;
}


BOOST_AUTO_TEST_SUITE_END()
