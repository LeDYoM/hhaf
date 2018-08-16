#pragma once

#ifndef LIB_RANDOMIZER_INCLUDE_HPP
#define LIB_RANDOMIZER_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib
{
	namespace core
	{
		class RandomizerPrivate;

		class Randomizer
		{
		public:
			Randomizer();
			virtual ~Randomizer();

			u32 getUInt(const size_type max = 1U, const size_type min = 0U) const;
		private:
			uptr<RandomizerPrivate> p_rPriv;
		};
	}
}

#endif
