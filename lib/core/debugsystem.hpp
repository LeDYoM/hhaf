#ifndef LIB_DEBUGSYSTEM_INCLUDE_HPP
#define LIB_DEBUGSYSTEM_INCLUDE_HPP

#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>
#include <lib/draw/components/debugvarscomponent.hpp>
#include <lib/include/compconfig.hpp>

#ifdef USE_DEBUG_VARIABLES
	#define DV_ONLY(x)	x
#else
	#define DV_ONLY(x)
#endif


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

			void showVarsNextFrame();
		private:
			draw::DebugVarAccessor m_matrixMultiplicationPerFrame;
		};
	}
}

#endif
