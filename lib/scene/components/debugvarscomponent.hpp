#pragma once

#ifndef LIB_DEBUGCOMPONENT_INCLUDE_HPP
#define LIB_DEBUGCOMPONENT_INCLUDE_HPP

#include <lib/scene/components/inputcomponent.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <map>

namespace lib
{
	namespace scene
	{
		class DebugVarsComponent final : public scene::InputComponent
		{
		public:
			DebugVarsComponent();
			virtual void update() override;
			void addOrUpdateDebugVar(const str &id, const str &data);
			void addOrUpdateDebugVar(const str &id, const u32 data);

			inline void showVarsNextFrame() noexcept { m_displayVarsNextFrame = true; }
		private:
			void displayDebugVars();

			std::map<str,str> m_varsData;
			bool m_displayVarsNextFrame{ false };
		};
	}
}

#endif
