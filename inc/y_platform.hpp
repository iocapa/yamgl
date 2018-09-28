#ifndef _Y_PLATFORM_HPP_
#define _Y_PLATFORM_HPP_

#if 0//defined(__cpp_constexpr) && __cpp_constexpr-0 >= 201304
#define Y_DECL_CONSTEXPR constexpr
#else
#define Y_DECL_CONSTEXPR
#endif

#endif