#pragma once

#ifndef ZOPER_MENUPAGETYPE_INCLUDE_HPP__
#define ZOPER_MENUPAGETYPE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>

namespace zoper
{
	enum class MenuPageType : lib::u32
	{
		Main					= 0,
		SelectLevelToken		= 1,
		SelectLevelSpeed		= 2,
		Options					= 3
	};
}

#endif