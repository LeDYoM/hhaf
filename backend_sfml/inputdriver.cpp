#include <backend_dev/include/ikey.hpp>

#include "inputdriver.hpp"
#include "conversions.hpp"

namespace haf::backend::sfmlb
{
InputDriver::InputDriver()  = default;
InputDriver::~InputDriver() = default;

void InputDriver::keyEvent(sf::Event const& e)
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

void InputDriver::keyPressed(IKey const key)
{
    keys_pressed_.push_back(key);
}

void InputDriver::keyReleased(IKey const key)
{
    keys_released_.push_back(key);
}

void InputDriver::readKeyPressed(htps::vector<IKey>& keys_pressed) const
{
    keys_pressed = keys_pressed_;
}

void InputDriver::readKeyReleased(htps::vector<IKey>& keys_released) const
{
    keys_released = keys_released_;
}

void InputDriver::clearInternalInputBuffer()
{
    keys_pressed_.clear();
    keys_released_.clear();
}

}  // namespace haf::backend::sfmlb
