#include <haf/include/input/key_manager.hpp>
#include "inputsystem.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/input/key.hpp>
#include "system/get_system.hpp"

namespace haf::input
{
bool KeyManager::registerKey(KeyIndex const key_index, Key const key) noexcept
{
    if (keys_.size() <= key_index)
    {
        auto const current_size = keys_.size();
        auto const desired_size = key_index + 1U;

        keys_.reserve(desired_size);

        std::fill(&keys_[current_size], std::end(keys_), Key::Unknown);
    }

    if (keys_[key_index] == Key::Unknown)
    {
        // The slot is free to register
        keys_[key_index] = key;
        return true;
    }

    return false;
}

Key KeyManager::keyForIndex(KeyIndex const key_index) const noexcept
{
    return ((keys_.size() > key_index) ? Key::Unknown : keys_[key_index]);
}

}  // namespace haf::input
