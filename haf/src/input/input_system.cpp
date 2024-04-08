#include "input_system.hpp"

#include <hlog/include/hlog.hpp>
#include "input_driver_wrapper.hpp"

using namespace haf::core;
using namespace haf::input;

namespace haf::sys
{

void InputSystem::setSharedKeyboardData(
    htps::sptr<input::KeyboardData> shared_keyboard_data)
{
    LogAsserter::log_assert(shared_keyboard_data != nullptr,
                            "Parameter is nullptr");
    LogAsserter::log_assert(m_shared_keyboard_data == nullptr,
                            "Shared keyboard data was already set");

    m_shared_keyboard_data = core::move(shared_keyboard_data);
}

void InputSystem::preUpdate()
{}

void InputSystem::update()
{
    m_shared_keyboard_data->pressedKeys.clear();
    KeyVector presed_keys_from_wrapper;
    input_driver_wrapper_->readKeyPressed(presed_keys_from_wrapper);
    for (auto const& key : presed_keys_from_wrapper)
    {
        keyPressed(key);
    }

    m_shared_keyboard_data->releasedKeys.clear();
    KeyVector released_keys_from_wrapper;
    input_driver_wrapper_->readKeyReleased(released_keys_from_wrapper);
    for (auto const& key : released_keys_from_wrapper)
    {
        keyReleased(key);
    }
}

void InputSystem::postUpdate()
{}

KeyStates const& InputSystem::keyStates() const noexcept
{
    return m_shared_keyboard_data->keyStates;
}

KeyState InputSystem::keyState(Key const key) const noexcept
{
    return m_shared_keyboard_data->keyStates[keyIndex(key)];
}

bool InputSystem::shiftPressed() const noexcept
{
    return keyState(Key::LShift) || keyState(Key::RShift);
}

bool InputSystem::controlPressed() const noexcept
{
    return keyState(Key::LControl) || keyState(Key::RControl);
}

const vector<Key>& InputSystem::pressedKeys() const noexcept
{
    return m_shared_keyboard_data->pressedKeys;
}

const vector<Key>& InputSystem::releasedKeys() const noexcept
{
    return m_shared_keyboard_data->releasedKeys;
}

void InputSystem::keyPressed(const Key key)
{
    LogAsserter::log_assert(isValidKey(key), "Incorrect key value");
    logger::DisplayLog::info("InputSystem: Key pressed: ", keyIndex(key));
    m_shared_keyboard_data->keyStates[keyIndex(key)] = true;
    m_shared_keyboard_data->pressedKeys.push_back(key);
}

void InputSystem::keyReleased(const Key key)
{
    LogAsserter::log_assert(isValidKey(key), "Incorrect key value");
    logger::DisplayLog::info("InputSystem: Key released: ", keyIndex(key));
    m_shared_keyboard_data->keyStates[keyIndex(key)] = false;
    m_shared_keyboard_data->releasedKeys.push_back(key);
}

void InputSystem::simulatePressKey(Key const key)
{
    keyPressed(key);
}

void InputSystem::simulateReleaseKey(Key const key)
{
    keyReleased(key);
}

}  // namespace haf::sys
