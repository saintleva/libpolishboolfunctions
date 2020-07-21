#ifndef __LIBPOLISHBOOLFUNCTIONS_SAMPLES_SIMPLIFIEDGENERATOR_I386NASMGENERATOR_H__
#define __LIBPOLISHBOOLFUNCTIONS_SAMPLES_SIMPLIFIEDGENERATOR_I386NASMGENERATOR_H__

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

#include <string>
#include <vector>
#include <ostream>
#include <stdexcept>
#include <boost/format.hpp>
#include <polishboolfunctions/exceptions.h>
#include <polishboolfunctions/Rpn.h>
#include <polishboolfunctions/Constant.h>
#include <polishboolfunctions/IndexedVariable.h>
#include <polishboolfunctions/NotOperation.h>
#include <polishboolfunctions/BinaryOperation.h>


class I386NasmGenerator {
public:

    typedef PolishBoolFunctions::IndexedVariable::Keeper Keeper;
    typedef PolishBoolFunctions::IndexedVariable::Index Index;
    typedef PolishBoolFunctions::Rpn Rpn;

    typedef std::string String;
    typedef String::size_type TextSize;
    typedef String::difference_type TextDifference;

    struct AsmCommand {

        typedef std::vector<String> StringContainer;

        inline explicit AsmCommand(const String& name):
            name(name), params() {}

        inline AsmCommand(const String& name, const String& param0):
            name(name), params(1)
        {
            params[0] = param0;
        }

        inline AsmCommand(const String& name, const String& param0, const String& param1):
            name(name), params(2)
        {
            params[0] = param0;
            params[1] = param1;
        }

        inline bool hasParams() const
        {
            return !params.empty();
        }

        String name;
        StringContainer params;

    }; //struct AsmCommand

    /* Construct/copy/destruct */

    inline I386NasmGenerator(TextSize cmdLeftIndent, TextSize paramsLeftIdent):
        cmdLeftIndent_(cmdLeftIndent), paramsLeftIdent_(paramsLeftIdent) {}

    void outputParams(std::ostream& stream, const AsmCommand::StringContainer& params);
    void outputCmd(std::ostream& stream, const AsmCommand& command);

    inline String byAddressAi(Index index) const
    {
        return (boost::format("[$a_%1%]") % index).str();
    }

    void generateEvaluator(std::ostream& stream, const Rpn& function) const;
    void generateIncrementatorByBlockSize(std::ostream& stream, Index varCount) const;

    static String binaryOperationCommandName(const PolishBoolFunctions::BinaryOperation& operation);

private:

    TextSize cmdLeftIndent_,
             paramsLeftIdent_;

}; //class I386NasmGenerator


#endif //__LIBPOLISHBOOLFUNCTIONS_SAMPLES_SIMPLIFIEDGENERATOR_I386NASMGENERATOR_H__
