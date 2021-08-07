#include "inputsystem.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/input/inputdriver_wrapper.hpp>

using namespace htps;
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

    input_driver_wrapper_ = std::move(input_driver_wrapper);
}

void InputSystem::preUpdate()
{}

void InputSystem::update()
{
    pressed_keys_.clear();
    decltype(pressed_keys_) presed_keys_from_wrapper;
    input_driver_wrapper_->readKeyPressed(presed_keys_from_wrapper);
    for (auto const& key : presed_keys_from_wrapper)
    {
        keyPressed(key);
    }

    released_keys_.clear();
    decltype(released_keys_) released_keys_from_wrapper;
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
    return key_states_;
}

KeyState InputSystem::keyState(Key const key) const
{
    return key_states_[keyIndex(key)];
}

const vector<Key>& InputSystem::pressedKeys() const noexcept
{
    return pressed_keys_;
}

const vector<Key>& InputSystem::releasedKeys() const noexcept
{
    return released_keys_;
}

void InputSystem::keyPressed(const Key key)
{
    LogAsserter::log_assert(isValidKey(key), "Incorrect key value");
    DisplayLog::info("InputSystem: Key pressed: ", keyIndex(key));
    key_states_[keyIndex(key)] = true;
    pressed_keys_.push_back(key);
}

void InputSystem::keyReleased(const Key key)
{
    LogAsserter::log_assert(isValidKey(key), "Incorrect key value");
    DisplayLog::info("InputSystem: Key released: ", keyIndex(key));
    key_states_[keyIndex(key)] = false;
    released_keys_.push_back(key);
}

void InputSystem::simulatePressKey(Key const key)
{
    input_driver_wrapper_->keyPressed(key);
}

void InputSystem::simulateReleaseKey(Key const key)
{
    input_driver_wrapper_->keyReleased(key);
}
}  // namespace haf::sys
