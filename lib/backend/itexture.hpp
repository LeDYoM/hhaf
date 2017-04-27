#ifndef LIB_BACKEND_ITEXTURE_HPP
#define LIB_BACKEND_ITEXTURE_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/include/rect.hpp>
#include <lib/draw/hasname.hpp>

namespace lib
{
	namespace backend
	{
		class ITexture : public core::HasName
		{
		public:
			using core::HasName::HasName;

			virtual ~ITexture() {}

			virtual vector2du32 size() const = 0;
		};
	}
}
#endif
