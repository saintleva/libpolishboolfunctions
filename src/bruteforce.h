#ifndef __LIBPOLISHBOOLFUNCTIONS_BRUTEFORCE_H__
#define __LIBPOLISHBOOLFUNCTIONS_BRUTEFORCE_H__

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

#include "ArgumentList.h"
#include "Rpn.h"
#include "RpnFunction.h"
#include "enumerate-vectors.h"
#include <iterator>

namespace PolishBoolFunctions {


//struct DoNothing {
//    inline static void process(const ArgumentList& argument) {}
//}; //struct DoNothing
//
//template<class OutputIterator> struct OutputByIterator {
//public:
//
//    inline OutputByIterator(OutputIterator iterator):
//        iterator_(iterator) {}
//
//    inline OutputIterator getIterator()
//    {
//        return iterator_;
//    }
//
//    inline void process()
//    {
//        *iterator_ = argument;
//    }
//
//private:
//    OutputIterator iterator_;
//
//}; //struct OutputByIterator

struct DoNothingIterator:
    public std::iterator<std::output_iterator_tag,void,void,void,void> {

    inline DoNothingIterator& operator=(const ArgumentList& argument) {}

    inline DoNothingIterator& operator*() {}

    inline DoNothingIterator& operator++() {}

    inline DoNothingIterator& operator++(int) {}

}; //struct DoNothingIterator


template<bool requiredResult, bool breakWhenFound, class ArgumentOutputIterator>
std::size_t bruteForceSearch(const PolishBoolFunctions::RpnFunction& function,
                             ArgumentOutputIterator outputIter)
{
    using namespace PolishBoolFunctions;

    std::size_t count = 0;

    ArgumentList current(function.arity, false);
    do
        if (evaluateRpn<DontCheck>(*function.rpn, current) == requiredResult)
        {
            ++count;
            *outputIter++ = current;
            if (breakWhenFound)
                break;
        }
    while (nextVector(current));

    return count;
}


} //namespace PolishBoolFunctions

#endif //__LIBPOLISHBOOLFUNCTIONS_BRUTEFORCE_H__
