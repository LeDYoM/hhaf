#include "debugvarscomponent.hpp"
#include <lib/include/liblog.hpp>

namespace lib::scene
{
    void DebugVarsComponent::displayDebugVars()
    {
        for (auto&& dv : m_varsData) {
            log_info(dv.first,": ",dv.second);
        }
    }

    DebugVarsComponent::DebugVarsComponent()
    {
/*      scene::InputComponent::setOnKeyPressedHandler([this](const auto&key) {
            if (key == input::Key::Num2) {
                m_displayVarsNextFrame = true;
            }
        });
        */
    }

    void DebugVarsComponent::update()
    {
        scene::InputComponent::update();

        if (isPressed(input::Key::Num1))
        {
            m_displayVarsNextFrame = true;
        }

        if (m_displayVarsNextFrame)
        {
            m_displayVarsNextFrame = false;
            displayDebugVars();
        }
    }

    void DebugVarsComponent::addOrUpdateDebugVar(const str &id, const str &data)
    {
        m_varsData[id] = data;
    }

    void DebugVarsComponent::addOrUpdateDebugVar(const str &, const u32)
    {
//      addOrUpdateDebugVar(id, str(data));
    }
}
