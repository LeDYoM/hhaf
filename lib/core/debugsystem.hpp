#ifndef LIB_DEBUGSYSTEM_INCLUDE_HPP
#define LIB_DEBUGSYSTEM_INCLUDE_HPP

#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>
#include <lib/core/log.hpp>
#include <lib/draw/icomponent.hpp>
#include <lib/draw/components/debugvarscomponent.hpp>

#include <vector>

namespace lib
{
	namespace draw
	{
		class Scene;
	}

	namespace core
	{

		class DebugSystem final : public AppService
		{
		public:
			DebugSystem();
			~DebugSystem();

			void addDebugVars(const sptr<draw::Scene> &scene);
			void setMatrixMultiplicationPerFrame(u32 &var);
		private:
			draw::DebugVarAccessor m_matrixMultiplicationPerFrame;
		};
	}
}

#endif
