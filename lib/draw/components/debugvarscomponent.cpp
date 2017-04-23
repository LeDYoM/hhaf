#include "debugvarscomponent.hpp"

namespace lib
{
	namespace draw
	{
		void DebugVarsComponent::displayDebugVars()
		{
			for (auto&& dv : m_varsData) {
				logDebug(dv());
			}
		}

		void DebugVarsComponent::update()
		{
			draw::InputComponent::update();

			if (isPressed(input::Key::Num1)) {
				m_displayVarsNextFrame = true;
			}

			if (m_displayVarsNextFrame) {
				m_displayVarsNextFrame = false;
				displayDebugVars();
			}
		}

		void DebugVarsComponent::addOrUpdateDebugVar(const str_const & id, str_const data)
		{
			const auto iterator(std::find_if(m_varsData.begin(), m_varsData.end(),
				[&id](const auto &dvi) noexcept { return dvi.id() == id; }
			));
			if (iterator != m_varsData.end()) {
				// Update
				iterator->setValue(std::move(data));
			}
			else {
				// Add
				m_varsData.emplace_back(std::move(id), std::move(data));
			}
		}
	}
}
