#ifndef __LIB_RANDOMIZER_HPP__
#define __LIB_RANDOMIZER_HPP__

#include <lib/include/types.hpp>

namespace lib
{
	class RandomizerPrivate;

	class Randomizer
	{
	public:
		Randomizer();
		virtual ~Randomizer();
		
		u32 getUInt(u32 max = 1, u32 min = 0) const;
	private:
		uptr<RandomizerPrivate> p_rPriv;
	};
}

#endif
