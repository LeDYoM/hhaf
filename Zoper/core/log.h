#ifndef __LOG_H__
#define __LOG_H__

#include "config.h"

#ifdef DEBUG
	#include <iostream>
	#define LOG_DEBUG(x)	std::cout << x << std::endl;
	#define LOG_ERROR(x)	std::cout << x << std::endl;
	
#endif

#endif
