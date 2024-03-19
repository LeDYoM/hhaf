#ifndef HAF_BACKEND_ICORE_MESSAGES_INCLUDE_HPP
#define HAF_BACKEND_ICORE_MESSAGES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <backend_dev/include/ikey.hpp>

namespace haf::backend
{
class ICoreMessages
{
public:
    virtual void keyPressed(IKey const& key) = 0;

    virtual void keyReleased(IKey const& key) = 0;

    virtual void requestExit();

protected:
    /**
     * @brief Destroy the ICoreMessages object
     */
    virtual ~ICoreMessages() = default;
};

}  // namespace haf::backend

#endif
