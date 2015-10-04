#include "log.hpp"

#if defined(_MSC_VER) || defined(__BORLANDC__)
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif
#include <iostream>


void logOutput(const char *str)
{
	std::cout << str;
#if defined(_MSC_VER) || defined(__BORLANDC__)
	OutputDebugString(str);
#endif
}
