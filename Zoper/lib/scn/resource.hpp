#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__

#include "../types.hpp"
#include "../core/hasname.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	namespace scn
	{
		class Resource : lib::core::HasName
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
