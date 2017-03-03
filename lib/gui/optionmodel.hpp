#ifndef LIB_GUI_OPTIONS_MODEL_INCLUDE_HPP__
#define LIB_GUI_OPTIONS_MODEL_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include <vector>
#include <functional>

namespace lib
{
	namespace gui
	{
		class OptionModel
		{
		public:
			explicit OptionModel(str_const&& text, string_vector subOptionsLabels = string_vector{})
				: text{ std::move(text) }, subOptionsLabels{ std::move(subOptionsLabels) } {}

			str_const text;
			string_vector subOptionsLabels;
		};
	}
}

#endif
