#include <haf/include/input/stated_input_component_base.hpp>
#include "inputsystem.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/input/key.hpp>
#include "system/get_system.hpp"

namespace haf::input
{

struct StatedInputComponentBase::StatedInputComponentBasePrivate
{
    vector<htps::pair<InputInState, InputInState>> data_;
    types::u32 current_state_;
};

StatedInputComponentBase::StatedInputComponentBase() :
    p_{htps::make_pimplp<StatedInputComponentBasePrivate>()}
{}

StatedInputComponentBase::~StatedInputComponentBase() = default;

void StatedInputComponentBase::addStateKeyInputFunction(
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

void StatedInputComponentBase::setProcessingState(
    types::u32 const current_state)
{
    p_->current_state_ = current_state;
}

void StatedInputComponentBase::onKeyPressed(Key const& key)
{
    auto const& functions{p_->data_[p_->current_state_]};
    if (functions.first)
    {
        functions.first(key);
    }
}

void StatedInputComponentBase::onKeyReleased(Key const& key)
{
    auto const& functions{p_->data_[p_->current_state_]};
    if (functions.second)
    {
        functions.second(key);
    }
}
}  // namespace haf::input
