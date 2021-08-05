#include "inputsystem.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/input/inputdriver_wrapper.hpp>

using namespace htps;
using namespace haf::input;

namespace haf::sys
{

void InputSystem::setInputDriverWrapper(sptr<InputDriverWrapper> input_driver_wrapper)
{
    LogAsserter::log_assert(input_driver_wrapper != nullptr, "Parameter is nullptr");
    LogAsserter::log_assert(input_driver_wrapper_ == nullptr,
                            "Input driver wrapper was already set");

    input_driver_wrapper_ = std::move(input_driver_wrapper);
}

void InputSystem::preUpdate()
{
}

void InputSystem::update()
{
    m_pressedKeys.clear();
    decltype(m_pressedKeys) presed_keys_from_wrapper;
    input_driver_wrapper_->readKeyPressed(presed_keys_from_wrapper);
    for (auto const& key : presed_keys_from_wrapper)
    {
        keyPressed(key);
    }

    m_releasedKeys.clear();
    decltype(m_releasedKeys) released_keys_from_wrapper;
    input_driver_wrapper_->readKeyReleased(released_keys_from_wrapper);
    for (auto const& key : released_keys_from_wrapper)
    {
        keyReleased(key);
    }
}

void InputSystem::postUpdate()
{
}

const vector<Key>& InputSystem::pressedKeys() const noexcept
{
    return m_pressedKeys;
}

const vector<Key>& InputSystem::releasedKeys() const noexcept
{
    return m_releasedKeys;
}

void InputSystem::keyPressed(const Key key)
{
    LogAsserter::log_assert(key < Key::KeyCount, "Incorrect key value");
    DisplayLog::info("InputSystem: Key pressed: ", KeyIndex(key));
    m_keyStates[KeyIndex(key)] = true;
    m_pressedKeys.push_back(key);
}

void InputSystem::keyReleased(const Key key)
{
    LogAsserter::log_assert(key < Key::KeyCount, "Incorrect key value");
    DisplayLog::info("InputSystem: Key released: ", KeyIndex(key));
    m_keyStates[KeyIndex(key)] = false;
    m_releasedKeys.push_back(key);
}

void InputSystem::simulatePressKey(const Key key)
{
    input_driver_wrapper_->keyPressed(key);
}

void InputSystem::simulateReleaseKey(const Key key)
{
    input_driver_wrapper_->keyReleased(key);
}
}  // namespace haf::sys
