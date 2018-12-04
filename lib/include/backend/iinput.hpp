#pragma once

#ifndef LIB_BACKEND_IINPUT_INCLUDE_HPP
#define LIB_BACKEND_IINPUT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/vertex.hpp>
#include <lib/include/key.hpp>
#include <lib/scene/vertexarray.hpp>
#include "itexture.hpp"

namespace lib
{
	namespace backend
	{
		class IInput
		{
		public:

			virtual ~IInput() {}

			virtual bool arePendingKeyPresses() const = 0;
			virtual bool arePendingKeyReleases() const = 0;

			virtual input::Key popKeyPress() = 0;
			virtual input::Key popKeyRelease() = 0;
		};
	}
}

#endif
