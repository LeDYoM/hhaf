#include <lib/input/include/key.hpp>

#include "inputdriver.hpp"
#include "conversions.hpp"

using namespace lib::input;

namespace lib::backend::sfmlb
{
void InputDriver::keyEvent(const sf::Event &e)
{
    const lib::input::Key k(doCast(e.key.code));
    if (k != Key::Unknown)
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
    return !m_keysPressed.empty();
}

bool InputDriver::arePendingKeyReleases() const
{
    return !m_keysReleased.empty();
}

template <typename T>
Key popKey(T &container)
{
    Key k(Key::Unknown);
    if (!container.empty())
    {
        k = container.front();
        container.pop();
    }
    return k;
}

Key InputDriver::popKeyPress()
{
    return popKey(m_keysPressed);
}

Key InputDriver::popKeyRelease()
{
    return popKey(m_keysReleased);
}

void InputDriver::keyPressed(const Key k)
{
    m_keysPressed.push(k);
}

void InputDriver::keyReleased(const Key k)
{
    m_keysReleased.push(k);
}
} // namespace lib::backend::sfmlb
