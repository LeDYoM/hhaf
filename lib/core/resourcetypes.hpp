#ifndef LIB_RESOURCETYPES_HPP__
#define LIB_RESOURCETYPES_HPP__

#include <mtypes/include/types.hpp>
#include <list>

namespace lib
{
	class IResourcesList;

	namespace scene
	{
		class TTFont;
		class Texture;
	}
	namespace core
	{
		class ResourceLoader;

		template <typename T>
		using NamedIndex = std::pair<const str, T>;

		template <typename T>
		using ResourceList = std::list<NamedIndex<T>>;

	}
}

#endif
