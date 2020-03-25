#pragma once

#ifndef MTPS_TYPES_EXT_HPP__
#define MTPS_TYPES_EXR_HPP__

#include <memory>
#include <iostream>

#include "str.hpp"

namespace mtps
{
    using write_stream = str;
    using read_stream = std::istream;
}

#endif
