#pragma once

#ifndef LIB_TYPES_EXT_HPP__
#define LIB_TYPES_EXR_HPP__

#include <memory>
#include <iostream>

#include "str.hpp"

namespace lib
{
	using write_stream = str;
	using read_stream = std::istream;
}

#endif
