#include <input/i_include/inputsystem.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/input/include/inputdriver.hpp>

using namespace htps;
using namespace haf::input;

namespace haf::sys
{

void InputSystem::setInputDriver(sptr<InputDriver> input_driver)
{
    LogAsserter::log_assert(input_driver != nullptr, "Parameter is nullptr");
    LogAsserter::log_assert(input_driver_ == nullptr,
                            "Input driver was already set");

    input_driver_ = std::move(input_driver);
}

void InputSystem::update()
{
    m_pressedKeys.clear();
    while (input_driver_->arePendingKeyPresses())
    {
        keyPressed(input_driver_->popKeyPress());
    }

    m_releasedKeys.clear();
    while (input_driver_->arePendingKeyReleases())
    {
        keyReleased(input_driver_->popKeyRelease());
    }
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
    input_driver_->keyPressed(key);
}

void InputSystem::simulateReleaseKey(const Key key)
{
    input_driver_->keyReleased(key);
}
}  // namespace haf::sys
