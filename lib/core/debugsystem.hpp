#ifndef LIB_DEBUGSYSTEM_INCLUDE_HPP
#define LIB_DEBUGSYSTEM_INCLUDE_HPP

#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>

namespace lib
{
	namespace core
	{
		class DebugSystem final : public AppService
		{
		public:
			DebugSystem();
			~DebugSystem();

		};
	}
}

#endif
