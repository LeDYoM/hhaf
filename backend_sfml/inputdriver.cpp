#include <backend_dev/include/ikey.hpp>

#include "inputdriver.hpp"
#include "conversions.hpp"

namespace haf::backend::sfmlb
{
void InputDriver::keyEvent(const sf::Event& e)
{
    const iKey k(doCast(e.key.code));
    if (k != iKey::Unknown)
    {
        if (e.type == sf::Event::KeyPressed)
        {
            keyPressed(k);
        }
        else if (e.type == sf::Event::KeyReleased)
        {
            keyReleased(k);
        }
    }
}

bool InputDriver::arePendingKeyPresses() const
{
    return !keysPressed_.empty();
}

bool InputDriver::arePendingKeyReleases() const
{
    return !keysReleased_.empty();
}

template <typename T>
iKey popKey(T& container)
{
    iKey k(iKey::Unknown);
    if (!container.empty())
    {
        k = container.front();
        container.pop();
    }
    return k;
}

iKey InputDriver::popKeyPress()
{
    return popKey(keysPressed_);
}

iKey InputDriver::popKeyRelease()
{
    return popKey(keysReleased_);
}

void InputDriver::keyPressed(const iKey k)
{
    keysPressed_.push(k);
}

void InputDriver::keyReleased(const iKey k)
{
    keysReleased_.push(k);
}
}  // namespace haf::backend::sfmlb
