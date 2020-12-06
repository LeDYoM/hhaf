#ifndef HAF_BACKEND_IINPUTDRIVER_INCLUDE_HPP
#define HAF_BACKEND_IINPUTDRIVER_INCLUDE_HPP

#include "ikey.hpp"

namespace haf::backend
{
/**
 * @brief This class defines an interface to be used by any class wanting to
 * provide keyboard data.
 */
class IInputDriver
{
public:
    /**
     * @brief Destroy the IInputDriver object
     */
    virtual ~IInputDriver() {}

    /**
     * @brief Ask if there is a pending press @b iKey ready to be read
     *
     * @return true There is a @b iKey press ready to be read
     * @return false The queue is empty.
     */
    virtual bool arePendingKeyPresses() const = 0;

    /**
     * @brief Ask if there is a pending release @b iKey ready to be read
     *
     * @return true There is a @b iKey release ready to be read
     * @return false The queue is empty.
     */
    virtual bool arePendingKeyReleases() const = 0;

    /**
     * @brief Extract the last @b iKey that has been pressed.
     * @return Key The extracted @b iKey
     */
    virtual iKey popKeyPress() = 0;

    /**
     * @brief Extract the last @b iKey that has been released.
     * @return Key The extracted @b iKey
     */
    virtual iKey popKeyRelease() = 0;

    /**
     * @brief Users of this class should call this method to add any
     * pending key pressed.
     *  @param[in] iKey indicating the element to add.
     */
    virtual void keyPressed(const iKey) = 0;

    /**
     * @brief Users of this class should call this method to add any
     * pending key released.
     *  @param[in] iKey indicating the element to add.
     */
    virtual void keyReleased(const iKey) = 0;
};
}  // namespace haf::backend

#endif
