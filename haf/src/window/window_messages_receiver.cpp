#include "window_messages_receiver.hpp"
#include <backend_dev/include/iwindow.hpp>

#include "input/input_system.hpp"
#include "input/input_driver_wrapper.hpp"

#include <hlog/include/hlog.hpp>

namespace haf::sys
{
WindowMessagesReceiver::WindowMessagesReceiver()  = default;
WindowMessagesReceiver::~WindowMessagesReceiver() = default;

void WindowMessagesReceiver::startInputKeysUpdate()
{
    m_keyboardData.pressedKeys.clear();
    m_keyboardData.releasedKeys.clear();
}

void WindowMessagesReceiver::endInputKeysUpdate()
{
}

void WindowMessagesReceiver::keyPressed(backend::IKey const& key)
{
    // Check that the key is not already inserted? Perhaps too slow
    m_keyboardData.pressedKeys.push_back(key);
}

void WindowMessagesReceiver::keyReleased(backend::IKey const&)
{
    m_keyboardData.releasedKeys.push_back(key);
}

void WindowMessagesReceiver::requestExit()
{
    m_exit_requested = true;
}

bool WindowMessagesReceiver::exitRequested() const noexcept
{
    return m_exit_requested;
}
}  // namespace haf::sys
