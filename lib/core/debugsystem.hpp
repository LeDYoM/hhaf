#ifndef LIB_DEBUGSYSTEM_INCLUDE_HPP
#define LIB_DEBUGSYSTEM_INCLUDE_HPP

#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>

namespace lib
{
	namespace gui
	{
		class TextGroup;
	}
	namespace core
	{
		class DebugSystem final : public AppService
		{
		public:
			DebugSystem();
			~DebugSystem();
		private:
			sptr<gui::TextGroup> m_debugVarsNode;
		};
	}
}

#endif
