#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__

#include <lib/include/types.hpp>
#include <lib/draw/hasname.hpp>
#include "log.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

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
			sf::Font *getAsFont() const { __ASSERT(_resourceType == ResourceType::Font, "Resource is not a font"); return _resourceData.font; }
			sf::Texture *getAsTexture() const { __ASSERT(_resourceType == ResourceType::Texture ,"Resource is not a font"); return _resourceData.texture; }
		private:
			bool _isValid{ false };
			union ResourceData
			{
				sf::Font *font{ nullptr };
				sf::Texture *texture;
			} _resourceData;
		};
	}
}

#endif
