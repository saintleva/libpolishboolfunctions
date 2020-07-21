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

#include "exceptions.h"
#include <boost/format.hpp>

using namespace PolishBoolFunctions;
using boost::format;


/* class Error */

Error::~Error() throw() {}


/* class VariableIndexOutOfArgListBounds */

VariableIndexOutOfArgListBounds::~VariableIndexOutOfArgListBounds() throw() {}

Error::String VariableIndexOutOfArgListBounds::what() const throw()
{
    return (format("Variable index %1% out of argument list bounds [0,%2%]") %
            getIndex() % (getArgListSize() - 1)).str();
}


/* class ArgumentDoesntAgreeWithArity */

ArgumentDoesntAgreeWithArity::~ArgumentDoesntAgreeWithArity() throw() {}

Error::String ArgumentDoesntAgreeWithArity::what() const throw()
{
    return (format("Argument (bit vector) has length %1% but boolean operation has arity %2%") %
            getActualArity() % getExpectedArity()).str();
}


//#if 0
///* class OperationsAreEquivalenceUntestable */
//
//OperationsAreEquivalenceUntestable::~OperationsAreEquivalenceUntestable() throw() {}
//#endif


/* class TokenIsNeitherOperandNorOperation */

TokenIsNeitherOperandNorOperation::~TokenIsNeitherOperandNorOperation() throw() {}

Error::String TokenIsNeitherOperandNorOperation::what() const throw()
{
    return "Invalid token: it is neither operand not operation";
}


/* class NotEnoughArgumentsForOperation */

NotEnoughArgumentsForOperation::~NotEnoughArgumentsForOperation() throw() {}

Error::String NotEnoughArgumentsForOperation::what() const throw()
{
    return (format("It is insufficient arguments (operands) for the operation (%1% required)") %
            getArity()).str();
}


/* class NotExactlyOneEvaluationResult */

NotExactlyOneEvaluationResult::~NotExactlyOneEvaluationResult() throw() {}

Error::String NotExactlyOneEvaluationResult::what() const throw()
{
    return (format("Result of the function (after evaluating) is %1%-sized but must be single") %
            getResultCount()).str();
}


/* class DontKnowHowToStringizeSomething */

DontKnowHowToStringizeSomething::~DontKnowHowToStringizeSomething() throw() {}


/* class OperationIsUnknown */

OperationIsUnknown::~OperationIsUnknown() throw() {}

Error::String OperationIsUnknown::what() const throw()
{
    return "Don't know how to stringize this operation because it is unknown to token output policy";
}
