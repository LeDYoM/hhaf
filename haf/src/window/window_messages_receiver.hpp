#ifndef HAF_WINDOW_WINDOW_MESSAGES_RECEIVER_INCLUDE_HPP
#define HAF_WINDOW_WINDOW_MESSAGES_RECEIVER_INCLUDE_HPP

#include <haf/include/core/types.hpp>

#include <backend_dev/include/iwindow_messages_receiver.hpp>
#include <backend_dev/include/ikey.hpp>

#include "input/keyboard_data.hpp"

namespace haf::sys
{
class WindowMessagesReceiver final : public backend::IWindowMessagesReceiver
{
public:
    WindowMessagesReceiver();
    ~WindowMessagesReceiver() override;

    void startInputKeysUpdate() override;
    void endInputKeysUpdate() override;
    void keyPressed(backend::IKey const& key) override;
    void keyReleased(backend::IKey const& key) override;
    void requestExit() override;

    bool exitRequested() const noexcept;

    core::sptr<input::KeyboardData> sharedKeyboardData();
    core::sptr<input::KeyboardData const> sharedKeyboardData() const;

private:
    bool m_exit_requested{false};
    core::sptr<input::KeyboardData> m_keyboardData;
};
}  // namespace haf::sys

#endif
