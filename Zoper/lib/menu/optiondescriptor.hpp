#ifndef __LIB_OPTIONDESCRIPTOR_HPP__
#define __LIB_OPTIONDESCRIPTOR_HPP__

#include <string>
#include "../types.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>

namespace lib
{
	namespace menu
	{
		class OptionDescriptor
		{
		public:
			explicit OptionDescriptor(const std::string &text, const vector2df &inc, u32 chSize, const sf::Color &color);
			virtual ~OptionDescriptor();

			inline const std::string getText() const { return _text; }
			inline const vector2df getInc() const { return _inc; }
			inline const u32 getCharSize() const { return _chSize; }
			inline const sf::Color getColor() const { return _color; }
		private:
			std::string _text;
			vector2df _inc;
			u32 _chSize;
			sf::Color _color;
		};
	}
}

#endif
