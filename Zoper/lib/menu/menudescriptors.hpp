#ifndef __LIB_MENUDESCRIPTOR_HPP__
#define __LIB_MENUDESCRIPTOR_HPP__

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
			explicit OptionDescriptor(const std::string &text, const sf::Color &color)
				: _text(text), _color{ color } {}
			virtual ~OptionDescriptor() {}

			inline const std::string getText() const { return _text; }
			inline const sf::Color getColor() const { return _color; }
		private:
			std::string _text;
			sf::Color _color;
		};

		class CursorDescriptor
		{
		public:
			explicit CursorDescriptor(const u32 nVertex, const vector2df &size, const sf::Color &color)
				: _nVertex{ nVertex }, _size{ size }, _color{ color } {}
			virtual ~CursorDescriptor() {}

			inline const u32 getNVertex() const { return _nVertex; }
			inline const vector2df getSize() const { return _size; }
			inline const sf::Color getColor() const { return _color; }
		private:
			u32 _nVertex;
			vector2df _size;
			sf::Color _color;
		};
	}
}

#endif
