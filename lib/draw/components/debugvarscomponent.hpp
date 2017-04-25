#ifndef LIB_DEBUGCOMPONENT_INCLUDE_HPP
#define LIB_DEBUGCOMPONENT_INCLUDE_HPP

#include <lib/include/types.hpp>
#include <lib/draw/icomponent.hpp>
#include <lib/draw/components/inputcomponent.hpp>
#include <lib/core/log.hpp>
#include <lib/include/debugvar.hpp>
#include <vector>

namespace lib
{
	namespace draw
	{
		class DebugVarsComponent final : public draw::InputComponent
		{
		public:
			virtual void update() override;
			void addOrUpdateDebugVar(DebugVarAccessor & dba, const str_const &id, str_const data);
			void addOrUpdateDebugVar(DebugVarAccessor & dba, const str_const &id, const u32 data);

			inline void showVarsNextFrame() noexcept { m_displayVarsNextFrame = true; }
		private:
			void displayDebugVars();

			std::vector<sptr<DebugVar>> m_varsData;
			bool m_displayVarsNextFrame{ false };
		};
	}
}

#endif
