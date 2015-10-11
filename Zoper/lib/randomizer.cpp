#include "randomizer.hpp"
#include <random>

#include "log.hpp"

namespace lib
{
	class RandomizerPrivate
	{
	public:
		std::random_device rd;
		std::mt19937 mt;

		RandomizerPrivate()
			: mt{ rd() }
		{
		}
		std::uniform_int_distribution<int> dist;
	};
	Randomizer::Randomizer()
		: p_rPriv{ new RandomizerPrivate() }
	{
		LOG_CONSTRUCT_NOPARAMS;
	}


	Randomizer::~Randomizer()
	{
		LOG_DESTRUCT_NOPARAMS;
	}

	u32 Randomizer::getUInt(u32 max /*= 1*/, u32 min/*=0*/)
	{
		LOG_DEBUG("Asked for random number between " << min << " and " << max);
		auto g = p_rPriv->dist(p_rPriv->mt) % (max - min);
		LOG_DEBUG("\tGot " << g);
		LOG_DEBUG("\tReturning " << min+g);
		return min + g;
	}

}
