#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__

#include <lib/include/types.hpp>
#include <lib/draw/hasname.hpp>
#include "log.hpp"
#include <lib/draw/font.hpp>
#include <lib/draw/texture.hpp>

namespace lib
{
	namespace core
	{
		class Resource : public lib::core::HasName
		{
		public:
			enum class ResourceType
			{
				Empty = 0,
				Font = 1,
				Texture = 2,
				MaxResourceType = 0xffff
			} _resourceType{ ResourceType::Empty };

			Resource(const Resource &) = delete;
			Resource(Resource &&other);
			Resource(ResourceType rType, const std::string &file, const std::string &id);
			virtual ~Resource();

			inline bool isValid() const { return _isValid; }
			draw::Font *getAsFont() const { __ASSERT(_resourceType == ResourceType::Font, "Resource is not a font"); return _resourceData.font; }
			draw::Texture *getAsTexture() const { __ASSERT(_resourceType == ResourceType::Texture ,"Resource is not a font"); return _resourceData.texture; }
		private:
			bool _isValid{ false };
			union ResourceData
			{
				draw::Font *font{ nullptr };
				draw::Texture *texture;
			} _resourceData;
		};
	}
}

#endif
