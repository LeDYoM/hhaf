#include <haf/include/input/stated_input_component.hpp>
#include "inputsystem.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/input/key.hpp>
#include "system/get_system.hpp"

namespace haf::input
{

struct StatedInputComponent::StatedInputComponentPrivate
{
    vector<htps::pair<InputInState, InputInState>> data_;
};

StatedInputComponent::StatedInputComponent() :
    p_{htps::make_pimplp<StatedInputComponentPrivate>()}
{}

StatedInputComponent::~StatedInputComponent() = default;

void StatedInputComponent::addStateKeyInputFunction(
    types::u32 const value,
    InputInState key_pressed_function,
    InputInState key_released_function)
{
    p_->data_.reserve(value + 1U);
    while (p_->data_.size() < (value + 1U))
    {
        p_->data_.emplace_back();
    }
    p_->data_[value] = {std::move(key_pressed_function),
                        std::move(key_released_function)};
}

void StatedInputComponent::onKeyPressed(Key const&)
{
    
}

void StatedInputComponent::onKeyReleased(Key const&)
{}
}  // namespace haf::input
