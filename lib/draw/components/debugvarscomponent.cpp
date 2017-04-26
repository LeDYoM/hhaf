#include "debugvarscomponent.hpp"

namespace lib
{
	namespace draw
	{
		void DebugVarsComponent::displayDebugVars()
		{
			for (auto&& dv : m_varsData) {
				logDebug((*dv)());
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

		void DebugVarsComponent::addOrUpdateDebugVar(DebugVarAccessor & dba, str_const_ id, str_const data)
		{
			const auto iterator(std::find(m_varsData.begin(), m_varsData.end(), dba));
			if (iterator != m_varsData.end()) {
				// Update
				(*iterator)->setValue(std::move(data));
				//return *iterator;
			}
			else {
				// Add
				m_varsData.emplace_back(msptr<DebugVar>(std::move(id), std::move(data)));
				dba = m_varsData[m_varsData.size() - 1];
				//return m_varsData[m_varsData.size() - 1];
			}
		}

		void DebugVarsComponent::addOrUpdateDebugVar(DebugVarAccessor & dba, const str_const_ id, const u32 data)
		{
			addOrUpdateDebugVar(dba, std::move(id), std::to_string(data));
		}
	}
}
