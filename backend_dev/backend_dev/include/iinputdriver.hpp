#ifndef HAF_BACKEND_IINPUTDRIVER_INCLUDE_HPP
#define HAF_BACKEND_IINPUTDRIVER_INCLUDE_HPP

#include <htypes/include/vector.hpp>
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
     * @brief Users of this class should call this method to add any
     * pending key pressed.
     *  @param[in] iKey indicating the element to add.
     */
    virtual void keyPressed(IKey const) = 0;

    /**
     * @brief Users of this class should call this method to add any
     * pending key released.
     *  @param[in] iKey indicating the element to add.
     */
    virtual void keyReleased(IKey const) = 0;

    virtual void clearInternalInputBuffer()                               = 0;
    virtual void readKeyPressed(htps::vector<IKey>& keys_pressed) const   = 0;
    virtual void readKeyReleased(htps::vector<IKey>& keys_released) const = 0;
};
}  // namespace haf::backend

#endif
