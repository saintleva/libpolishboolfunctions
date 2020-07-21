/*
 * Copyright (c) Anton Liaukevich 2009 <leva.dev@gmail.com>
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

#include "generate.h"
#include <iostream>
#include <polishboolfunctions/io.h>
#include <polishboolfunctions/plaintext-output.h>


int main()
{
    using namespace PolishBoolFunctions;

//    IndexedVariable::Keeper keeper1(6);
//    Rpn rpn1;
//    rpn1.push_back(TokenPtr(new IndexedVariable(&keeper1, 3)));
//    rpn1.push_back(TokenPtr(new IndexedVariable(&keeper1, 4)));
//    rpn1.push_back(TokenPtr(new IndexedVariable(&keeper1, 2)));
//    rpn1.push_back(TokenPtr(new IndexedVariable(&keeper1, 5)));
//    rpn1.push_back(TokenPtr(UnaryOperators::Not.clone()));
//    rpn1.push_back(TokenPtr(new IndexedVariable(&keeper1, 0)));
//    rpn1.push_back(TokenPtr(BinaryOperators::Or.clone()));
//    rpn1.push_back(TokenPtr(new IndexedVariable(&keeper1, 1)));
//    rpn1.push_back(TokenPtr(BinaryOperators::Xor.clone()));
//    rpn1.push_back(TokenPtr(BinaryOperators::Xor.clone()));
//    rpn1.push_back(TokenPtr(BinaryOperators::And.clone()));

    IndexedVariable::Keeper keeper2(4);
    Rpn rpn2;
    rpn2.push_back(TokenPtr(new IndexedVariable(&keeper2, 0)));
    rpn2.push_back(TokenPtr(UnaryOperators::Not.clone()));
    rpn2.push_back(TokenPtr(new IndexedVariable(&keeper2, 1)));
    rpn2.push_back(TokenPtr(new IndexedVariable(&keeper2, 2)));
    rpn2.push_back(TokenPtr(BinaryOperators::Or.clone()));
    rpn2.push_back(TokenPtr(BinaryOperators::And.clone()));
    rpn2.push_back(TokenPtr(new IndexedVariable(&keeper2, 2)));
    rpn2.push_back(TokenPtr(new IndexedVariable(&keeper2, 1)));
    rpn2.push_back(TokenPtr(BinaryOperators::Xor.clone()));
    rpn2.push_back(TokenPtr(new IndexedVariable(&keeper2, 0)));
    rpn2.push_back(TokenPtr(new IndexedVariable(&keeper2, 1)));
    rpn2.push_back(TokenPtr(UnaryOperators::Not.clone()));
    rpn2.push_back(TokenPtr(BinaryOperators::Or.clone()));
    rpn2.push_back(TokenPtr(new IndexedVariable(&keeper2, 2)));
    rpn2.push_back(TokenPtr(new IndexedVariable(&keeper2, 3)));
    rpn2.push_back(TokenPtr(BinaryOperators::Or.clone()));
    rpn2.push_back(TokenPtr(BinaryOperators::Xor.clone()));
    rpn2.push_back(TokenPtr(BinaryOperators::And.clone()));
    rpn2.push_back(TokenPtr(new IndexedVariable(&keeper2, 0)));
    rpn2.push_back(TokenPtr(BinaryOperators::Xor.clone()));
    rpn2.push_back(TokenPtr(BinaryOperators::Or.clone()));

    using namespace PlaintextIO;
    std::cout << "HORIZONTAL OUTPUT:\n";
    outputRpn<TokenOutputPolicy<TextualOperationSymbols>,SimpleHorizontalOutputer>(std::cout, rpn2);
    std::cout << "\n\n";

    std::cout << "EVALUATOR FOR I386:\n";
    generateEvaluatorForI386(std::cout, rpn2);
    std::cout << "\n\n";

//    std::cout << "BLOCK INCREMENTATOR FOR I386:\n";
//    generateIncrementatorByBlockSize(std::cout, 32, 10);

    return 0;
}
