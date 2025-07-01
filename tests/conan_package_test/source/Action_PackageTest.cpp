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

#include <cstdio>
#include "action/Action.h"

void printEnvironment(const char* version)
{
#ifdef NDEBUG
    printf("action_test/%s: Action Test Release\n", version);
#else
    printf("action_test/%s: Action Test Debug\n", version);
#endif

// ARCHITECTURES
#ifdef _M_X64
    printf("  action_test/%s: _M_X64 defined\n", version);
#endif

#ifdef _M_IX86
    printf("  action_test/%s: _M_IX86 defined\n", version);
#endif

#ifdef _M_ARM64
    printf("  action_test/%s: _M_ARM64 defined\n", version);
#endif

#if __i386__
    printf("  action_test/%s: __i386__ defined\n", version);
#endif

#if __x86_64__
    printf("  action_test/%s: __x86_64__ defined\n", version);
#endif

#if __aarch64__
    printf("  action_test/%s: __aarch64__ defined\n", version);
#endif

// Libstdc++
#if defined _GLIBCXX_USE_CXX11_ABI
    printf("  action_test/%s: _GLIBCXX_USE_CXX11_ABI %d\n", version, _GLIBCXX_USE_CXX11_ABI);
#endif

// MSVC runtime
#if defined(_DEBUG)
    #if defined(_MT) && defined(_DLL)
        printf("  action_test/%s: MSVC runtime: MultiThreadedDebugDLL\n", version);
    #elif defined(_MT)
        printf("  action_test/%s: MSVC runtime: MultiThreadedDebug\n", version);
    #endif
#else
    #if defined(_MT) && defined(_DLL)
        printf("  action_test/%s: MSVC runtime: MultiThreadedDLL\n", version);
    #elif defined(_MT)
        printf("  action_test/%s: MSVC runtime: MultiThreaded\n", version);
    #endif
#endif

// COMPILER VERSIONS
#if _MSC_VER
    printf("  action_test/%s: _MSC_VER %d\n", version, _MSC_VER);
#endif

#if _MSVC_LANG
    printf("  action_test/%s: _MSVC_LANG %d\n", version, _MSVC_LANG);
#endif

#if __cplusplus
    printf("  action_test/%s: __cplusplus %d\n", version, __cplusplus);
#endif

#if __INTEL_COMPILER
    printf("  action_test/%s: __INTEL_COMPILER %d\n", version, __INTEL_COMPILER);
#endif

#if __GNUC__
    printf("  action_test/%s: __GNUC__ %d\n", version, __GNUC__);
#endif

#if __GNUC_MINOR__
    printf("  action_test/%s: __GNUC_MINOR__%d\n", version, __GNUC_MINOR__);
#endif

#if __clang_major__
    printf("  action_test/%s: __clang_major__ %d\n", version, __clang_major__);
#endif

#if __clang_minor__
    printf("  action_test/%s: __clang_minor__ %d\n", version, __clang_minor__);
#endif

#if __apple_build_version__
    printf("  action_test/%s: __apple_build_version__ %d", version, __apple_build_version__);
#endif

// SUBSYSTEMS
#if __MSYS__
    printf("  action_test/%s: __MSYS__ %d\n", version, __MSYS__);
#endif

#if __MINGW32__
    printf("  action_test/%s: __MINGW32__ %d\n", version, __MINGW32__);
#endif

#if __MINGW64__
    printf("  action_test/%s: __MINGW64__ %d\n", version, __MINGW64__);
#endif

#if __CYGWIN__
    printf("  action_test/%s: __CYGWIN__ %d\n", version, __CYGWIN__);
#endif
}

// Simple program that tests that the meen_hw package is configured correctly.
// It then prints out the meen_hw version along with environment information.
int main()
{
    printEnvironment(action::Version());
    return 0;
}
