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
}

void WindowMessagesReceiver::endInputKeysUpdate()
{
}

void WindowMessagesReceiver::keyPressed(backend::IKey const&)
{}

void WindowMessagesReceiver::keyReleased(backend::IKey const&)
{}

void WindowMessagesReceiver::requestExit()
{
    m_exit_requested = true;
}

bool WindowMessagesReceiver::exitRequested() const noexcept
{
    return m_exit_requested;
}
}  // namespace haf::sys
