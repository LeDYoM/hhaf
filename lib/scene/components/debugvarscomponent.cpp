#include "debugvarscomponent.hpp"

namespace lib
{
	namespace scene
	{
		void DebugVarsComponent::displayDebugVars()
		{
			for (auto&& dv : m_varsData) {
				log_debug_info(dv.first,": ",dv.second);
			}
		}

		DebugVarsComponent::DebugVarsComponent()
		{
/*			scene::InputComponent::setOnKeyPressedHandler([this](const auto&key) {
				if (key == input::Key::Num2) {
					m_displayVarsNextFrame = true;
				}
			});
			*/
		}

		void DebugVarsComponent::update()
		{
			scene::InputComponent::update();

			if (isPressed(input::Key::Num1)) {
				m_displayVarsNextFrame = true;
			}

			if (m_displayVarsNextFrame) {
				m_displayVarsNextFrame = false;
				displayDebugVars();
			}
		}

		void DebugVarsComponent::addOrUpdateDebugVar(const str &id, const str &data)
		{
			m_varsData[id] = data;
		}

		void DebugVarsComponent::addOrUpdateDebugVar(const str &id, const u32 data)
		{
//			addOrUpdateDebugVar(id, str(data));
		}
	}
}
