#ifndef LIB_DEBUGSYSTEM_INCLUDE_HPP
#define LIB_DEBUGSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/core/appservice.hpp>
#include <lib/scene/components/debugvarscomponent.hpp>
#include <lib/include/compconfig.hpp>

#ifdef USE_DEBUG_VARIABLES
	#define DV_ONLY(x)	x
#else
	#define DV_ONLY(x)
#endif


namespace lib
{
	namespace scene
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

			void addDebugVars(const sptr<scene::Scene> &scene);
			void setMatrixMultiplicationPerFrame(u32 &var);
			void showVarsNextFrame();
		};
	}
}

#endif
