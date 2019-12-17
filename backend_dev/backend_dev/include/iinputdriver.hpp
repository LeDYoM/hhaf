#pragma once

#ifndef LIB_BACKEND_IINPUTDRIVER_INCLUDE_HPP
#define LIB_BACKEND_IINPUTDRIVER_INCLUDE_HPP

#include <lib/include/key.hpp>

namespace lib::backend
{
/// @brief This class defines an interface to be used
/// by any class wanting to provide keyboard data.
class IInputDriver
{
public:
    /// Virtual destructor to enable inheritance correctly.
    virtual ~IInputDriver() {}

    /// @return This method returns true if there are any pressed @Key
    /// ready to be read
    virtual bool arePendingKeyPresses() const = 0;

    /// @return This method returns true if there are any released @Key
    /// ready to be read
    virtual bool arePendingKeyReleases() const = 0;

    /// Extract the last @Key that has been pressed.
    /// @return The extracted @Key
    virtual input::Key popKeyPress() = 0;

    /// Extract the last @Key that has been released.
    /// @return The extracted @Key
    virtual input::Key popKeyRelease() = 0;

    /// Users of this class should call this method to add any
    /// pending key pressed.
    /// @param[in] input::Key indicating the element to add.
    virtual void keyPressed(const input::Key) = 0;

    /// Users of this class should call this method to add any
    /// pending key releases.
    /// @param[in] input::Key indicating the element to add.
    virtual void keyReleased(const input::Key) = 0;
};
} // namespace lib::backend

#endif
