#include "input_system.hpp"

#include <hlog/include/hlog.hpp>
#include "input_driver_wrapper.hpp"

using namespace haf::core;
using namespace haf::input;

namespace haf::sys
{

void InputSystem::setInputDriverWrapper(
    sptr<InputDriverWrapper> input_driver_wrapper)
{
    LogAsserter::log_assert(input_driver_wrapper != nullptr,
                            "Parameter is nullptr");
    LogAsserter::log_assert(input_driver_wrapper_ == nullptr,
                            "Input driver wrapper was already set");

    input_driver_wrapper_ = htps::move(input_driver_wrapper);
}

void InputSystem::preUpdate()
{}

void InputSystem::update()
{
    m_keyboard_data.pressedKeys.clear();
    KeyVector presed_keys_from_wrapper;
    input_driver_wrapper_->readKeyPressed(presed_keys_from_wrapper);
    for (auto const& key : presed_keys_from_wrapper)
    {
        keyPressed(key);
    }

    m_keyboard_data.releasedKeys.clear();
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
    return m_keyboard_data.keyStates;
}

KeyState InputSystem::keyState(Key const key) const noexcept
{
    return m_keyboard_data.keyStates[keyIndex(key)];
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
    return m_keyboard_data.pressedKeys;
}

const vector<Key>& InputSystem::releasedKeys() const noexcept
{
    return m_keyboard_data.releasedKeys;
}

void InputSystem::keyPressed(const Key key)
{
    LogAsserter::log_assert(isValidKey(key), "Incorrect key value");
    logger::DisplayLog::info("InputSystem: Key pressed: ", keyIndex(key));
    m_keyboard_data.keyStates[keyIndex(key)] = true;
    m_keyboard_data.pressedKeys.push_back(key);
}

void InputSystem::keyReleased(const Key key)
{
    LogAsserter::log_assert(isValidKey(key), "Incorrect key value");
    logger::DisplayLog::info("InputSystem: Key released: ", keyIndex(key));
    m_keyboard_data.keyStates[keyIndex(key)] = false;
    m_keyboard_data.releasedKeys.push_back(key);
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
