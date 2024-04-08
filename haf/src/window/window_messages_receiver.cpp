#include "window_messages_receiver.hpp"
#include <backend_dev/include/iwindow.hpp>

#include "input/input_system.hpp"

#include <hlog/include/hlog.hpp>

using namespace haf::core;
using namespace haf::input;
using namespace haf::backend;

namespace
{
constexpr Key toKey(IKey const ikey) noexcept
{
    return static_cast<Key>(ikey);
}

}  // namespace

namespace haf::sys
{
WindowMessagesReceiver::WindowMessagesReceiver() :
    m_keyboardData{core::msptr<input::KeyboardData>()}
{}

WindowMessagesReceiver::~WindowMessagesReceiver() = default;

void WindowMessagesReceiver::startInputKeysUpdate()
{
    m_keyboardData->pressedKeys.clear();
    m_keyboardData->releasedKeys.clear();
}

void WindowMessagesReceiver::endInputKeysUpdate()
{}

void WindowMessagesReceiver::keyPressed(IKey const& key)
{
    // Check that the key is not already inserted? Perhaps too slow.
    m_keyboardData->pressedKeys.push_back(toKey(key));
}

void WindowMessagesReceiver::keyReleased(IKey const& key)
{
    m_keyboardData->releasedKeys.push_back(toKey(key));
}

void WindowMessagesReceiver::requestExit()
{
    m_exit_requested = true;
}

bool WindowMessagesReceiver::exitRequested() const noexcept
{
    return m_exit_requested;
}

sptr<KeyboardData> WindowMessagesReceiver::sharedKeyboardData()
{
    return m_keyboardData;
}

sptr<KeyboardData const> WindowMessagesReceiver::sharedKeyboardData() const
{
    return m_keyboardData;
}

}  // namespace haf::sys
