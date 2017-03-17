#include "randomizer.hpp"
#include <random>

#include "log.hpp"
#include "config.h"

namespace lib
{
	namespace core
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
			logConstruct_NOPARAMS;
		}


		Randomizer::~Randomizer()
		{
			logDestruct_NOPARAMS;
		}

		u32 Randomizer::getUInt(u32 max, u32 min) const
		{
			logDebug("Asked for random number between ", min, " and ", max);
			__ASSERT(min != max, "The min and max parameters must be different");
			__ASSERT(max > min, "The max paramter must be greater than min");
			auto g = p_rPriv->dist(p_rPriv->mt) % (max - min);
			logDebug("\tGot ", g);
			logDebug("\tReturning ", min + g);
			return min + g;
		}
	}
}
