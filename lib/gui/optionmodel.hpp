#ifndef LIB_GUI_OPTIONS_MODEL_INCLUDE_HPP__
#define LIB_GUI_OPTIONS_MODEL_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <vector>
#include <functional>
#include <initializer_list>

namespace lib
{
	namespace gui
	{
		class OptionModelIndex : public std::vector<u32>
		{
		public:
			OptionModelIndex() = default;
			constexpr OptionModelIndex(const OptionModelIndex&rhs) = default;
			constexpr OptionModelIndex(OptionModelIndex&&rhs) = default;
			OptionModelIndex& operator=(OptionModelIndex&&) = default;
			OptionModelIndex& operator=(const OptionModelIndex&) = default;

			constexpr OptionModelIndex(std::initializer_list<u32> il) : std::vector<u32>{ std::move(il) } {}
			constexpr OptionModelIndex(const std::vector<u32>&rhs) : std::vector<u32>{ rhs } {}
			constexpr OptionModelIndex(std::vector<u32>&&rhs) : std::vector<u32>{ std::move(rhs) } {}

		};

		class OptionModel
		{
		public:
			explicit OptionModel(str text, string_vector subOptionsLabels = {}, OptionModelIndex next = {})
				: text{ std::move(text) }, subOptionsLabels{ std::move(subOptionsLabels) }, next{std::move(next)} {}
			constexpr OptionModel(const OptionModel&rhs) = default;
			constexpr OptionModel(OptionModel&&) = default;
			OptionModel &operator=(const OptionModel&) = default;
			OptionModel &operator=(OptionModel&&) = default;

			str text;
			string_vector subOptionsLabels;
			OptionModelIndex next;
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
