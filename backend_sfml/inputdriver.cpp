#include <backend_dev/include/ikey.hpp>

#include "inputdriver.hpp"
#include "conversions.hpp"

namespace haf::backend::sfmlb
{
void InputDriver::keyEvent(const sf::Event& e)
{
    const IKey k(doCast(e.key.code));
    if (k != IKey::Unknown)
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
IKey popKey(T& container)
{
    IKey k(IKey::Unknown);
    if (!container.empty())
    {
        k = container.front();
        container.pop();
    }
    return k;
}

IKey InputDriver::popKeyPress()
{
    return popKey(keysPressed_);
}

IKey InputDriver::popKeyRelease()
{
    return popKey(keysReleased_);
}

void InputDriver::keyPressed(const IKey k)
{
    keysPressed_.push(k);
}

void InputDriver::keyReleased(const IKey k)
{
    keysReleased_.push(k);
}
}  // namespace haf::backend::sfmlb
