#ifndef __LIB_EVENT_HPP__
#define __LIB_EVENT_HPP__

#include <lib/include/key.hpp>

namespace lib
{
	namespace events
	{
		class Event
		{
		public:
			Event() {}
			virtual ~Event() {}
		};
	}
}
#endif
