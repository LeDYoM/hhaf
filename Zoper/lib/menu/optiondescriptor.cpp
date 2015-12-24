#include "optiondescriptor.hpp"

namespace lib
{
	namespace menu
	{
		OptionDescriptor::OptionDescriptor(const std::string &text, const vector2df &inc, u32 chSize, const sf::Color &color)
			: _text(text), _inc{ inc }, _chSize{ chSize }, _color{ color }
		{

		}

		OptionDescriptor::~OptionDescriptor()
		{
		}
	}
}
