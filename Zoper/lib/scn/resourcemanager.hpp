#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include "../types.hpp"
#include <SFML/Graphics/Font.hpp>

namespace lib
{
	namespace scn
	{
		class ResourceManager
		{
		public:
			ResourceManager();
			virtual ~ResourceManager();
			sptr<sf::Font> getFont() const;

		private:
			std::map<std::string, sptr<sf::Font>> fonts;

		};
	}
}

#endif
