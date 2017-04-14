#include "debugsystem.hpp"

#include "log.hpp"

namespace lib
{
	namespace core
	{
		DebugSystem::DebugSystem()
		{
			logConstruct_NOPARAMS;
		}

		DebugSystem::~DebugSystem()
		{
			logDestruct_NOPARAMS;
		}
	}
}
