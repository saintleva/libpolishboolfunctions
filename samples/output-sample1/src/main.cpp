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

#include <iostream>
#include <polishboolfunctions/Rpn.h>
#include <polishboolfunctions/Constant.h>
#include <polishboolfunctions/Variable.h>
#include <polishboolfunctions/NotOperation.h>
#include <polishboolfunctions/BinaryOperation.h>
#include <polishboolfunctions/ArgumentList.h>
#include <polishboolfunctions/io.h>
#include <polishboolfunctions/plaintext-output.h>


int main()
{
    using namespace PolishBoolFunctions;

    Rpn rpn1;
    rpn1.push_back(TokenPtr(new Constant(false)));
    rpn1.push_back(TokenPtr(new Constant(true)));
    rpn1.push_back(TokenPtr(BinaryOperators::AndNot.clone()));
    rpn1.push_back(TokenPtr(new Constant(false)));
    rpn1.push_back(TokenPtr(BinaryOperators::AndNot.clone()));
    rpn1.push_back(TokenPtr(new Constant(true)));
    rpn1.push_back(TokenPtr(new Variable(2)));
    rpn1.push_back(TokenPtr(new Constant(true)));
    rpn1.push_back(TokenPtr(UnaryOperators::Not.clone()));
    rpn1.push_back(TokenPtr(new Variable(0)));
    rpn1.push_back(TokenPtr(BinaryOperators::Or.clone()));
    rpn1.push_back(TokenPtr(new Variable(1)));
    rpn1.push_back(TokenPtr(BinaryOperators::Implies.clone()));
    rpn1.push_back(TokenPtr(BinaryOperators::Xor.clone()));
    rpn1.push_back(TokenPtr(BinaryOperators::Xor.clone()));
    rpn1.push_back(TokenPtr(BinaryOperators::And.clone()));

    using namespace PlaintextIO;
    std::cout << "HORIZONTAL OUTPUT:\n";
    outputRpn<TokenOutputPolicy<TextualOperationSymbols>,SimpleHorizontalOutputer>(std::cout, rpn1);
    std::cout << "\n"
              << "VERTICAL OUTPUT:\n";
    outputRpn<TokenOutputPolicy<TextualOperationSymbols>,SimpleVerticalOutputer>(std::cout, rpn1);

    ArgumentList args1(10);
    args1[0] = true;
    args1[1] = true;
    args1[2] = false;
    args1[3] = true;

    evaluateRpn<DoCheck>(rpn1, args1);

    return 0;
}
