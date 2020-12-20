#include <haf/input/include/key_manager.hpp>
#include <input/i_include/inputsystem.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/input/include/key.hpp>
#include <system/i_include/get_system.hpp>

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
