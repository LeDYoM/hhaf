#ifndef HAF_INPUT_KEYBOARD_DATA_INCLUDE_HPP
#define HAF_INPUT_KEYBOARD_DATA_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/input/key.hpp>

namespace haf::input
{
using KeyVector = core::vector<Key>;

struct KeyboardData final
{
    KeyStates keyStates{false};
    KeyVector pressedKeys;
    KeyVector releasedKeys;
};

}  // namespace haf::input

#endif
