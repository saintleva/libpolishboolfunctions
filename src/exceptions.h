#ifndef __LIBPOLISHBOOLFUNCTIONS_EXCEPTIONS_H__
#define __LIBPOLISHBOOLFUNCTIONS_EXCEPTIONS_H__

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

#include "Token.h"
#include "ArgumentList.h"
#include "AbstractOperation.h"
#include "Rpn.h"
#include <string>

namespace PolishBoolFunctions {


class Error {
public:
    typedef std::string String;
    virtual String what() const throw() = 0;

protected:
    virtual ~Error() throw();

}; //class Error

class VariableIndexOutOfArgListBounds: public Error {
public:
    typedef ArgumentList::size_type Size;

    inline VariableIndexOutOfArgListBounds(Size index, Size argListSize):
        index_(index), argListSize_(argListSize) {}

    virtual ~VariableIndexOutOfArgListBounds() throw();

    inline Size getIndex() const
    {
        return index_;
    }

    inline Size getArgListSize() const
    {
        return argListSize_;
    }

    virtual String what() const throw();

private:
    Size index_, argListSize_;

}; //class VariableIndexOutOfArgListBounds

class ArgumentDoesntAgreeWithArity: public Error {
public:

    inline ArgumentDoesntAgreeWithArity(AbstractOperation::Arity actualArity,
                                        AbstractOperation::Arity expectedArity):
        actualArity_(actualArity), expectedArity_(expectedArity) {}

    virtual ~ArgumentDoesntAgreeWithArity() throw();

    inline AbstractOperation::Arity getActualArity() const
    {
        return actualArity_;
    }

    inline AbstractOperation::Arity getExpectedArity() const
    {
        return expectedArity_;
    }

    virtual String what() const throw();

private:
    AbstractOperation::Arity actualArity_, expectedArity_;

}; //class ArgumentDoesntAgreeWithArity

///**
// * @todo: Can such an exceptions be useful in my library?
// */
//#if 0
//class OperationsAreEquivalenceUntestable {
//public:
//
//    inline OperationsAreEquivalenceUntestable(const AbstractOperation* operation1,
//                                              const AbstractOperation* operation2):
//        operation1_(operation1), operation2_(operation2) {}
//
//    inline const AbstractOperation* getOperation1() const
//    {
//        return operation1_;
//    }
//
//    inline const AbstractOperation* getOperation2() const
//    {
//        return operation2_;
//    }
//
//protected:
//    virtual ~OperationsAreEquivalenceUntestable() throw();
//
//private:
//    const AbstractOperation *operation1_, *operation2_;
//
//}; //class OperationsAreEquivalenceUntestable
//
//struct OperationsAreOfDifferentTypes: public Error, public OperationsAreEquivalenceUntestable {
//
//    inline VariablesAreOfDifferentTypes(const Variable* variable1, const Variable* variable2):
//        VariablesAreNotRelated(variable1, variable2) {}
//    virtual ~VariablesAreOfDifferentTypes() throw();
//
//    virtual String what() const throw();
//
//}; //struct VariablesAreOfDifferentTypes
//#endif

struct RpnIsInvalid {};

class TokenIsNeitherOperandNorOperation: public Error, public RpnIsInvalid {
public:

    inline explicit TokenIsNeitherOperandNorOperation(const Token* token):
        token_(token) {}

    virtual ~TokenIsNeitherOperandNorOperation() throw();

    inline const Token* getToken() const
    {
        return token_;
    }

    virtual String what() const throw();

private:
    const Token* token_;

}; //class TokenIsNeitherOperandNorOperation

class NotEnoughArgumentsForOperation: public Error, public RpnIsInvalid {
public:

    inline explicit NotEnoughArgumentsForOperation(Rpn::const_iterator iteratorToOperation):
        iteratorToOperation_(iteratorToOperation) {}

    virtual ~NotEnoughArgumentsForOperation() throw();

    inline Rpn::const_iterator getIteratorToOperation() const
    {
        return iteratorToOperation_;
    }

    inline Rpn::size_type getArity() const
    {
        return static_cast<AbstractOperation*>(iteratorToOperation_->get())->getArity();
    }

    virtual String what() const throw();

private:
    Rpn::const_iterator iteratorToOperation_;

}; //class NotEnoughArgumentsForOperation

class NotExactlyOneEvaluationResult: public Error, public RpnIsInvalid {
public:

    inline explicit NotExactlyOneEvaluationResult(Rpn::size_type resultCount):
        resultCount_(resultCount) {}

    virtual ~NotExactlyOneEvaluationResult() throw();

    inline Rpn::size_type getResultCount() const
    {
        return resultCount_;
    }

    virtual String what() const throw();

private:
    Rpn::size_type resultCount_;

}; //class NotExactlyOneEvaluationResult

class DontKnowHowToStringizeSomething {
public:

    inline DontKnowHowToStringizeSomething(const Token *token):
        token_(token) {}

    inline const Token* getToken() const
    {
        return token_;
    }

protected:
    virtual ~DontKnowHowToStringizeSomething() throw();

private:
    const Token* token_;

}; //class DontKnowHowToStringizeSomething

struct OperationIsUnknown: public Error, public DontKnowHowToStringizeSomething {

    inline OperationIsUnknown(const AbstractOperation* operation):
        DontKnowHowToStringizeSomething(operation) {}

    virtual ~OperationIsUnknown() throw();

    inline const AbstractOperation* getOperation() const
    {
        return static_cast<const AbstractOperation*>(getToken());
    }

    virtual String what() const throw();

}; //struct OperationIsUnknown


} //namespace PolishBoolFunctions

#endif //__LIBPOLISHBOOLFUNCTIONS_EXCEPTIONS_H__
