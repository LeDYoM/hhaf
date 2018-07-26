#pragma once

#ifndef LIB_BACKEND_ISHADERFACTORY_HPP
#define LIB_BACKEND_ISHADERFACTORY_HPP

#include <mtypes/include/types.hpp>

#include "ishader.hpp"

namespace lib::backend
{
	class IShaderFactory
	{
	public:
		virtual IShader* loadFromFile(const str &file) = 0;
		virtual ~IShaderFactory() {}
	};
}
#endif
