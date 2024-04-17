#ifndef HAF_BACKEND_IWINDOW_MESSAGES_RECEIVER_INCLUDE_HPP
#define HAF_BACKEND_IWINDOW_MESSAGES_RECEIVER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <backend_dev/include/ikey.hpp>

namespace haf::backend
{
class IWindowMessagesReceiver
{
public:
    virtual void startInputKeysUpdate() = 0;
    virtual void endInputKeysUpdate() = 0;
    virtual void keyPressed(IKey const& key) = 0;
    virtual void keyReleased(IKey const& key) = 0;
    virtual void requestExit() = 0;

protected:
    /**
     * @brief Destroy the IWindowMessagesReceiver object
     */
    virtual ~IWindowMessagesReceiver() = default;
};

}  // namespace haf::backend

#endif
