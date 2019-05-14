#pragma once

#ifndef LIB_SCENE_ITEXTURE_INTERFACE_INCLUDE_HPP
#define LIB_SCENE_ITEXTURE_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

namespace lib::scene
{
	class ITexture
	{
	public:
		virtual ~ITexture() {}
		virtual vector2du32 size() const = 0;
	};
}

#endif
