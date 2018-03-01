#pragma once

#ifndef LIB_CLASSMACROS_INCLUDE_
#define LIB_CLASSMACROS_INCLUDE_

#include <mtypes/include/types.hpp>
#include <mtypes/include/types_ext.hpp>

#define QUOTE__TEXT__(x)	#x

#define LOBJECT_CLASS_DECLARE(className,baseClass)		class className : public baseClass		\
														private:	\
															using BaseClass = baseClass;	\
															constexpr static char[] BaseClassString = "QUOTE__TEXT__(x)"	\
														private:

#endif
