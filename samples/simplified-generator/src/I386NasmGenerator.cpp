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

#include "I386NasmGenerator.h"
#include <string>
//#include <algorithm>
#include <boost/format.hpp>
#include <polishboolfunctions/IndexedVariable.h>
#include <polishboolfunctions/AbstractOperation.h>
#include <polishboolfunctions/BinaryOperation.h>
#include <polishboolfunctions/NotOperation.h>

using namespace PolishBoolFunctions;


void I386NasmGenerator::outputParams(std::ostream& stream, const AsmCommand::StringContainer& params)
{
    typedef AsmCommand::StringContainer::size_type Size;
    Size count = params.size();
    for (Size i = 0; i < count; ++i)
    {
        stream << params[i];
        if (i + 1 < count)
            stream << ", ";
    }
}

void I386NasmGenerator::outputCmd(std::ostream& stream, const AsmCommand& command)
{
    stream << String(cmdLeftIndent_, ' ') << command.name;
    if (command.hasParams())
    {
        TextSize interspace = std::max(static_cast<TextDifference>(paramsLeftIdent_) -
                                       static_cast<TextDifference>(command.name.length()), 1);
        stream << String(interspace, ' ');
        outputParams(stream, command.params);
    }
    stream << "\n";
}

I386NasmGenerator::String I386NasmGenerator::binaryOperationCommandName(const BinaryOperation& operation)
{
    using namespace BinaryOperators;

    if (operation.isEquivalentTo(Xor))
        return "xor";
    if (operation.isEquivalentTo(And))
        return "and";
    if (operation.isEquivalentTo(Or))
        return "or";
    throw std::invalid_argument("This binary operation not supported");
}

void I386NasmGenerator::generateEvaluator(std::ostream& stream, const Rpn& _function) const
{
    Rpn::size_type stackSize = 0,
                   maxStackSize = 0;

    // /* RPN must be started with variable */

    const Rpn& function = _function;

    Rpn::const_iterator current = function.begin();

    enum TokenType { FINISHED, VARIABLE, UNARY, BINARY };

    struct Auxiliary {

        static TokenType typeOf(const Rpn::const_iterator& token)
        {
            if (token == function.end())
                return FINISHED;
            if (dynamic_cast<IndexedVariable*>(token->get()))
                return VARIABLE;
            if (dynamic_cast<NotOperation*>(token->get()))
                return UNARY;
            if (dynamic_cast<BinaryOperation*>(token->get()))
                return BINARY;
            throw std::invalid_argument("This token is not supported");
        }

        static TokenType currentType()
        {
            return typeOf(current);
        }

        static TokenType nextType()
        {
            Rpn::const_iterator next = current + 1;
            //++next;
            return typeOf(next);
        }

        static String topStackAddress()
        {
            return (boost::format("[$stack + %1%*4]") % (stackSize - 1)).str();
        }

        static void generatePushToStack()
        {
            ++stackSize;
            if (stackSize > maxStackSize)
                maxStackSize = stackSize;
            outputCmd(stream, AsmCommand("mov", topStackAddress(), "eax"));
        }

        static void generateOperationPopingFromStack(const BinaryOperation& operation)
        {
            if (stackSize == 0)
                throw std::invalid_argument("Stack for intermediate variables is empty");
            outputCmd(stream, AsmCommand(binaryOperationCommandName(operation), "eax",
                                         topStackAddress()));
            --stackSize;
        }

        static void LookForward()
        {
            if (currentType() == VARIABLE)
                switch (nextType())
                {
                    case VARIABLE:
                    case UNARY:
                        generatePushToStack();
                        break;
                    case BINARY:
                        break;
                    case FINISHED:
                        throw NotExactlyOneEvaluationResult(stackSize + 1);
                        //throw std::invalid_argument("FINISHED");
                        break;
                }
        }

    }; //struct Auxiliary


    while (current != function.end())
    {
        if (IndexedVariable* var1 = dynamic_cast<IndexedVariable*>(current->get()))
        {
            outputCmd(stream, AsmCommand("mov", "eax", byAddressAi(var1->getIndex())));
            ++current;
            if (dynamic_cast<NotOperation*>(current->get())) // UNARY
            {
                outputCmd(stream, AsmCommand("not", "eax"));
                ++current;

                /* See forward */
                if (currentType(function, current) == VARIABLE)
                    switch (nextType(function, current))
                    {
                        case VARIABLE:
                        case UNARY:
                            generatePushToStack(stream, stackSize, maxStackSize);
                            break;
                        case BINARY:
                            break;
                        case FINISHED:
                            throw NotExactlyOneEvaluationResult(stackSize + 1);
                            //throw std::invalid_argument("FINISHED");
                            break;
                    }
            }
            else if (currentType(function, current) == VARIABLE)
                switch (nextType(function, current))
                {
                    case VARIABLE:
                    case UNARY:
                        generatePushToStack(stream, stackSize, maxStackSize);
                        break;
                    case BINARY:
                    {
                        IndexedVariable* var2 = dynamic_cast<IndexedVariable*>(current->get());
                        ++current;
                        BinaryOperation* operation = dynamic_cast<BinaryOperation*>(current->get());
                        outputCmd(stream, AsmCommand(binaryOperationCommandName(*operation), "eax",
                                                     byAddressAi(var2->getIndex())));
                        ++current;
                        /* See forward */
                        if (currentType(function, current) == VARIABLE)
                            switch (nextType(function, current))
                            {
                                case VARIABLE:
                                case UNARY:
                                    generatePushToStack(stream, stackSize, maxStackSize);
                                    break;
                                case BINARY:
                                    break;
                                case FINISHED:
                                    throw NotExactlyOneEvaluationResult(stackSize + 1);
                                    //throw std::invalid_argument("FINISHED");
                                    break;
                            }
                            break;
                    }
                    case FINISHED:
                        throw NotExactlyOneEvaluationResult(stackSize + 1);
                        break;
                }
        }
        else if (dynamic_cast<NotOperation*>(current->get())) // UNARY
        {
            outputCmd(stream, AsmCommand("not", "eax"));
            ++current;
        }
        else if (BinaryOperation* operation = dynamic_cast<BinaryOperation*>(current->get())) // BINARY
        {
            generateOperationPopingFromStack(stream, stackSize, *operation);
            ++current;

            /* See forward */
            if (currentType(function, current) == VARIABLE)
                switch (nextType(function, current))
                {
                    case VARIABLE:
                    case UNARY:
                        generatePushToStack(stream, stackSize, maxStackSize);
                        break;
                    case BINARY:
                        break;
                    case FINISHED:
                        throw NotExactlyOneEvaluationResult(stackSize + 1);
                        //throw std::invalid_argument("FINISHED");
                        break;
                }
        }
        else
            throw std::invalid_argument("This token or situation not supported");
        stream << "------------------------\n";
    }

    stream << "Intermediate stack size: " << maxStackSize << "\n";
}
