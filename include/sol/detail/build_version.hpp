// sol2

// The MIT License (MIT)

// Copyright (c) 2013-2021 Rapptz, ThePhD and contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

#ifndef SOL_DETAIL_BUILD_VERSION_HPP
#define SOL_DETAIL_BUILD_VERSION_HPP

#include <sol/version.hpp>

// clang-format off

#if defined(SOL_BUILD)
	#if (SOL_BUILD != 0)
		#define SOL_BUILD_I_ SOL_ON
	#else
		#define SOL_BUILD_I_ SOL_OFF
	#endif
#else
	#define SOL_BUILD_I_ SOL_DEFAULT_OFF
#endif // Building or not

#if defined(SOL_DLL)
	#if (SOL_DLL != 0)
		#define SOL_DLL_I_ SOL_ON
	#else
		#define SOL_DLL_I_ SOL_OFF
	#endif
#elif SOL_IS_ON() && (defined(DLL_) || defined(_DLL))
	#define SOL_DLL_I_ SOL_DEFAULT_ON
#else
	#define SOL_DLL_I_ SOL_DEFAULT_OFF
#endif // DLL definition

#if defined(SOL_HEADER_ONLY)
	#if (SOL_HEADER_ONLY != 0)
		#define SOL_HEADER_ONLY_I_ SOL_ON
	#else
		#define SOL_HEADER_ONLY_I_ SOL_OFF
	#endif
#else
	#define SOL_HEADER_ONLY_I_ SOL_DEFAULT_OFF
#endif // Header only library

#if defined(SOL_UNITY_BUILD)
	#if (SOL_UNITY_BUILD != 0)
		#define SOL_UNITY_BUILD_I_ SOL_ON
	#else
		#define SOL_UNITY_BUILD_I_ SOL_OFF
	#endif
#else
	#define SOL_UNITY_BUILD_I_ SOL_DEFAULT_OFF
#endif // Header only library

#if defined(SOL_C_FUNCTION_LINKAGE)
	#define SOL_C_FUNCTION_LINKAGE_I_ SOL_C_FUNCTION_LINKAGE
#else
	#if SOL_IS_ON(SOL_BUILD_CXX_MODE_I_)
		// C++
		#define SOL_C_FUNCTION_LINKAGE_I_ extern "C"
	#else
		// normal
		#define SOL_C_FUNCTION_LINKAGE_I_
	#endif // C++ or not
#endif // Linkage specification for C functions

#if defined(SOL_API_LINKAGE)
	#define SOL_API_LINKAGE_I_ SOL_API_LINKAGE
#else
	#if SOL_IS_ON(SOL_DLL_I_)
		#if SOL_IS_ON(SOL_COMPILER_VCXX_I_) || SOL_IS_ON(SOL_PLATFORM_WINDOWS_I_) || SOL_IS_ON(SOL_PLATFORM_CYGWIN_I_)
			// MSVC Compiler; or, Windows, or Cygwin platforms
			#if SOL_IS_ON(SOL_BUILD_I_)
				// Building the library
				#if SOL_IS_ON(SOL_COMPILER_GCC_I_)
					// Using GCC
					#define SOL_API_LINKAGE_I_ __attribute__((dllexport))
				#else
					// Using Clang, MSVC, etc...
					#define SOL_API_LINKAGE_I_ __declspec(dllexport)
				#endif
			#else
				#if SOL_IS_ON(SOL_PLATFORM_GCC_I_)
					#define SOL_API_LINKAGE_I_ __attribute__((dllimport))
				#else
					#define SOL_API_LINKAGE_I_ __declspec(dllimport)
				#endif
			#endif
		#else
			// extern if building normally on non-MSVC
			#define SOL_API_LINKAGE_I_ extern
		#endif
	#elif SOL_IS_ON(SOL_UNITY_BUILD_I_)
		// Built-in library, like how stb typical works
		#if SOL_IS_ON(SOL_HEADER_ONLY_I_)
			// Header only, so functions are defined "inline"
			#define SOL_API_LINKAGE_I_ inline
		#else
			// Not header only, so seperately compiled files
			#define SOL_API_LINKAGE_I_ extern
		#endif
	#else
		// Normal static library
		#if SOL_IS_ON(SOL_BUILD_CXX_MODE_I_)
			#define SOL_API_LINKAGE_I_
		#else
			#define SOL_API_LINKAGE_I_ extern
		#endif
	#endif // DLL or not
#endif // Build definitions

#if defined(SOL_PUBLIC_FUNC_DECL)
	#define SOL_PUBLIC_FUNC_DECL_I_ SOL_PUBLIC_FUNC_DECL
#else
	#define SOL_PUBLIC_FUNC_DECL_I_ SOL_API_LINKAGE_I_
#endif

#if defined(SOL_INTERNAL_FUNC_DECL_)
	#define SOL_INTERNAL_FUNC_DECL_I_ SOL_INTERNAL_FUNC_DECL_
#else
	#define SOL_INTERNAL_FUNC_DECL_I_ SOL_API_LINKAGE_I_
#endif

#if defined(SOL_PUBLIC_FUNC_DEF)
	#define SOL_PUBLIC_FUNC_DEF_I_ SOL_PUBLIC_FUNC_DEF
#else
	#define SOL_PUBLIC_FUNC_DEF_I_ SOL_API_LINKAGE_I_
#endif

#if defined(SOL_INTERNAL_FUNC_DEF)
	#define SOL_INTERNAL_FUNC_DEF_I_ SOL_INTERNAL_FUNC_DEF
#else
	#define SOL_INTERNAL_FUNC_DEF_I_ SOL_API_LINKAGE_I_
#endif

// clang-format on 

#endif // SOL_DETAIL_BUILD_VERSION_HPP
