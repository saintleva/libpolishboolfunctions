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
#include <string>
#include <boost/format.hpp>
#include <polishboolfunctions/IndexedVariable.h>
#include <polishboolfunctions/AbstractOperation.h>
#include <polishboolfunctions/BinaryOperation.h>
#include <polishboolfunctions/NotOperation.h>

#include <iostream> //TODO: remove it


using namespace PolishBoolFunctions;


typedef std::string::size_type Size;
const Size cmdLeftIndent = 4;
const Size paramsLeftIdent = 10;

struct AsmCommand {

    typedef std::vector<std::string>::size_type ParamIndex;

    inline explicit AsmCommand(const std::string& name):
        name(name), params() {}

    inline AsmCommand(const std::string& name, const std::string& param0):
        name(name), params(1)
    {
        params[0] = param0;
    }

    inline AsmCommand(const std::string& name, const std::string& param0, const std::string& param1):
        name(name), params(2)
    {
        params[0] = param0;
        params[1] = param1;
    }

    inline bool hasParams() const
    {
        return !params.empty();
    }

    std::string name;
    std::vector<std::string> params;

}; //struct AsmCommand

void ouputParams(std::ostream& stream, const AsmCommand& command)
{
    AsmCommand::ParamIndex count = command.params.size();
    for (AsmCommand::ParamIndex i = 0; i + 1 < count; ++i)
        stream << command.params[i] << ", ";
    if (count >= 1)
        stream << command.params[count - 1];
}

void outputCmd(std::ostream& stream, const AsmCommand& command)
{
    stream << std::string(cmdLeftIndent, ' ');
    std::string name = command.name;
    stream << name;
    if (command.hasParams())
    {
        if (name.length() + 1 <= paramsLeftIdent)
            stream << std::string(paramsLeftIdent - name.length(), ' ');
        else
            stream << " ";
        ouputParams(stream, command);
    }
    stream << "\n";
}

std::string byAddressAi(Index index)
{
    return (boost::format("[$a_%1%]") % index).str();
}

void generateEvaluatorForStackedI386(std::ostream& stream, const Rpn& function)
{
    for (Rpn::const_iterator iter = function.begin(); iter != function.end(); ++iter)
        if (IndexedVariable* variable = dynamic_cast<IndexedVariable*>(iter->get()))
            outputCmd(stream, AsmCommand("push", byAddressAi(variable->getIndex())));
        else if (AbstractOperation* operation = dynamic_cast<AbstractOperation*>(iter->get()))
        {
            using namespace UnaryOperators;
            using namespace BinaryOperators;

            if (operation->isEquivalentTo(Not))
                outputCmd(stream, AsmCommand("not"));
            else if (operation->isEquivalentTo(Xor))
                outputCmd(stream, AsmCommand("xor"));
            else if (operation->isEquivalentTo(And))
                outputCmd(stream, AsmCommand("and"));
            else if (operation->isEquivalentTo(Or))
                outputCmd(stream, AsmCommand("or"));
            else
                throw std::invalid_argument("Operation not supported");
        }
        else
            throw std::invalid_argument("Only indexed variables and some operations are supported");
}

enum TokenType { FINISHED, VARIABLE, UNARY, BINARY };

TokenType currentType(const Rpn& function, Rpn::const_iterator current)
{
    if (current == function.end())
        return FINISHED;
    if (dynamic_cast<IndexedVariable*>(current->get()))
        return VARIABLE;
    if (dynamic_cast<NotOperation*>(current->get()))
        return UNARY;
    if (dynamic_cast<BinaryOperation*>(current->get()))
        return BINARY;
    throw std::invalid_argument("This token is not supported");
}

TokenType nextType(const Rpn& function, Rpn::const_iterator current)
{
    ++current;
    if (current == function.end())
        return FINISHED;
    if (dynamic_cast<IndexedVariable*>(current->get()))
        return VARIABLE;
    if (dynamic_cast<NotOperation*>(current->get()))
        return UNARY;
    if (dynamic_cast<BinaryOperation*>(current->get()))
        return BINARY;
    throw std::invalid_argument("This token is not supported");
}

TokenType nextNextType(const Rpn& function, Rpn::const_iterator current)
{
    ++current;
    ++current;
    if (current == function.end())
        return FINISHED;
    if (dynamic_cast<IndexedVariable*>(current->get()))
        return VARIABLE;
    if (dynamic_cast<NotOperation*>(current->get()))
        return UNARY;
    if (dynamic_cast<BinaryOperation*>(current->get()))
        return BINARY;
    throw std::invalid_argument("This token is not supported");
}

std::string binaryOperationCommandName(const BinaryOperation& operation)
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

void generatePushToStack(std::ostream& stream, Rpn::size_type& stackSize, Rpn::size_type& maxStackSize)
{
    ++stackSize;
    if (stackSize > maxStackSize)
        maxStackSize = stackSize;
    std::string topAddress = (boost::format("[$stack + %1%*4]") % (stackSize - 1)).str();
    outputCmd(stream, AsmCommand("mov", topAddress, "eax"));
}

void generateOperationPopingFromStack(std::ostream& stream, Rpn::size_type& stackSize,
                                      const BinaryOperation& operation)
{
    if (stackSize == 0)
        throw std::invalid_argument("Stack for intermediate variables is empty");
    std::string topAddress = (boost::format("[$stack + %1%*4]") % (stackSize - 1)).str();
    outputCmd(stream, AsmCommand(binaryOperationCommandName(operation), "eax", topAddress));
    --stackSize;
}

void generateEvaluatorForI386(std::ostream& stream, const Rpn& function)
{
    Rpn::size_type stackSize = 0,
                   maxStackSize = 0;

    // /* RPN must be started with variable */

    Rpn::const_iterator current = function.begin();
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

//void generateEvaluatorForI386(std::ostream& stream, const Rpn& function)
//{
//    using namespace UnaryOperators;
//    using namespace BinaryOperators;
//
//    Rpn::size_type stackSize = 0,
//                   maxStackSize = 0;
//
//    Rpn::const_iterator current = function.begin();
//    while (current != function.end())
//    {
//        if (AbstractOperation* operation = dynamic_cast<AbstractOperation*>(current->get()))
//            if (operation->isEquivalentTo(Not))
//            {
//                outputCmd(stream, AsmCommand("not", "eax"));
//                ++current;
//            }
//            else
//                throw std::invalid_argument("Only not (as it is unary) operation can be here");
//        else if (IndexedVariable* var1 = dynamic_cast<IndexedVariable*>(current->get()))
//        {
//            ++current;
//            if (AbstractOperation* operation = dynamic_cast<AbstractOperation*>(current->get()))
//            {
//                if (operation->isEquivalentTo(Not))
//                {
//                    outputCmd(stream, AsmCommand("mov", "eax", byAddressAi(var1->getIndex())));
//                    outputCmd(stream, AsmCommand("not", "eax"));
//                }
//                else if (operation->getArity() == 2)
//                {
//                    if (stackSize < 1)
//                        throw std::invalid_argument("Insufficiently arguments for binary operation");
//                    std::string rightArg = (boost::format("[$stack + %1%*4]") % (stackSize - 1)).str();
//
//                    std::string opStr;
//                    if (operation->isEquivalentTo(Xor))
//                        opStr = "xor";
//                    else if (operation->isEquivalentTo(And))
//                        opStr = "and";
//                    else if (operation->isEquivalentTo(Or))
//                        opStr = "or";
//                    else
//                        throw std::invalid_argument("This binary operation not supported");
//
//                    outputCmd(stream, AsmCommand(opStr, "eax", rightArg));
//                    --stackSize;
//                }
//                else
//                    throw std::invalid_argument("Unknown operation");
//                ++current;
//            }
//        }
////        if (!variable)
////            throw std::invalid_argument("Indexed variable must be here");
//    }
//}

template<class Integer>
Integer log2(Integer number)
{
    Integer result = 0;
    while (number != 1)
    {
        ++result;
        number >>= 1;
    }
    return result;
}

AsmCommand zeroCompareCommand(const std::string& object, bool isRegister)
{
    if (isRegister)
        return AsmCommand("test", (boost::format("%1%, %1%") % object).str());
    else
        return AsmCommand("cmp", object + ", 0");
}

void generateIncrementatorByBlockSize(std::ostream& stream, Index blockSize, Index varCount)
{
    Index start = log2(blockSize);
    for (Index index = start; index < start + varCount; ++index)
    {
        outputCmd(stream, AsmCommand("not", byAddressAi(index)));
        outputCmd(stream, zeroCompareCommand(byAddressAi(index), false));
        outputCmd(stream, AsmCommand("jnz $.continueSearch"));
    }
}
