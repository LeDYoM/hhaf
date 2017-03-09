#ifndef LIB_GUI_OPTIONS_MODEL_INCLUDE_HPP__
#define LIB_GUI_OPTIONS_MODEL_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include <vector>
#include <functional>
#include <initializer_list>

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

		class OptionModelIndex : public std::vector<u32> 
		{
		public:
			OptionModelIndex() : std::vector<u32>{} {}
			OptionModelIndex(std::initializer_list<u32> il) : std::vector<u32>{ std::move(il) } {}
			OptionModelIndex(const std::vector<u32>&rhs) : std::vector<u32>{ rhs } {}
			OptionModelIndex(std::vector<u32>&&rhs) : std::vector<u32>{ std::move(rhs) } {}
		};

		inline write_stream& operator<<(write_stream & os, const OptionModelIndex &mIndex)
		{
			os << "{";
			for (std::size_t i = 0; i < mIndex.size(); ++i) {
				os << mIndex[i];
				if (i < (mIndex.size() - 1)) {
					os << ",";
				}
			}
			os << "}";
			return os;
		}

	}


}

#endif
