#ifndef __LIB_MENUDESCRIPTOR_HPP__
#define __LIB_MENUDESCRIPTOR_HPP__

#include <string>
#include <lib/include/types.hpp>
#include <SFML/Graphics/Color.hpp>

namespace lib
{
	namespace menu
	{
		class OptionDescriptor
		{
		public:
			explicit OptionDescriptor(const std::string &text, bool createSubString=false,u32 startValueIndex=0,
				const std::vector<std::string> &subOptionsLabels=std::vector<std::string>())
				: _text(text), _createSubString{ createSubString }, _startValueIndex{ startValueIndex },
				_subOptionsLabels( subOptionsLabels ) {}

			std::string _text;
			bool _createSubString;
			u32 _startValueIndex;
			std::vector<std::string> _subOptionsLabels;
		};
	}
}

#endif
