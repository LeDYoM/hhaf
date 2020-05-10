#pragma once

#ifndef HAF_BACKEND_IINPUTDRIVER_INCLUDE_HPP
#define HAF_BACKEND_IINPUTDRIVER_INCLUDE_HPP

#include <haf/input/include/key.hpp>

namespace haf::backend
{
/// @brief This class defines an interface to be used
/// by any class wanting to provide keyboard data.
class IInputDriver
{
public:
    /**
     * @brief Destroy the IInputDriver object
     */
    virtual ~IInputDriver() {}

    /// @return This method returns true if there are any pressed @Key
    /// ready to be read

    /**
     * @brief Ask if there is a pending press @b Key ready to be read
     *
     * @return true There is a @b Key press ready to be read
     * @return false The queue is empty.
     */
    virtual bool arePendingKeyPresses() const = 0;

    /**
     * @brief Ask if there is a pending release @b Key ready to be read
     *
     * @return true There is a @b Key release ready to be read
     * @return false The queue is empty.
     */
    virtual bool arePendingKeyReleases() const = 0;

    /**
     * @brief Extract the last @Key that has been pressed.
     * @return Key The extracted @Key
     */
    virtual input::Key popKeyPress() = 0;

    /**
     * @brief Extract the last @Key that has been released.
     * @return Key The extracted @Key
     */
    virtual input::Key popKeyRelease() = 0;

    /**
     * @brief Users of this class should call this method to add any
     * pending key pressed.
     *  @param[in] Key indicating the element to add.
     */
    virtual void keyPressed(const input::Key) = 0;

    /**
     * @brief Users of this class should call this method to add any
     * pending key released.
     *  @param[in] Key indicating the element to add.
     */
    virtual void keyReleased(const input::Key) = 0;
};
}  // namespace haf::backend

#endif
