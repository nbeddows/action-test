/*
Copyright (c) 2021-2025 Nicolas Beddows <nicolas.beddows@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MEEN_HW_MH_FACTORY_H
#define MEEN_HW_MH_FACTORY_H

#include <memory>

#ifdef _WINDOWS
#ifdef action_STATIC
#define DLL_EXP_IMP
#elif defined action_EXPORTS
#define DLL_EXP_IMP __declspec(dllexport)
#else
#define DLL_EXP_IMP __declspec(dllimport)
#endif
#else
#ifdef action_EXPORTS
#define DLL_EXP_IMP [[gnu::visibility("default")]]
#else
#define DLL_EXP_IMP
#endif
#endif

namespace action
{
	DLL_EXP_IMP const char* Version();

	DLL_EXP_IMP std::unique_ptr<int> MakeActionTest();
} // namespace meen_hw

#endif // MEEN_HW_MH_FACTORY_H