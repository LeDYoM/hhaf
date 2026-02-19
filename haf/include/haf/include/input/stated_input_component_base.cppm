module;

#include "system/get_system.hpp"

export module haf:input:stated_input_component_base;

import :virtual_input_component;
import :key;
import :core;

namespace haf::input
{
struct StatedInputComponentBase::StatedInputComponentBasePrivate
{
    vector<pair<InputInState, InputInState>> data_;
    core::u32 current_state_;
};

class StatedInputComponentBase : public VirtualInputComponent
{
    using BaseClass = VirtualInputComponent;

public:
    using InputInState = htps::function<void(Key const&)>;

    StatedInputComponentBase() :
        p_{htps::make_pimplp<StatedInputComponentBasePrivate>()}
    {}

    ~StatedInputComponentBase() override = default;

    void onKeyPressed(Key const&) override
    {
        auto const& functions{p_->data_[p_->current_state_]};
        if (functions.first)
        {
            functions.first(key);
        }
    }

    void onKeyReleased(Key const&) override
    {
        auto const& functions{p_->data_[p_->current_state_]};
        if (functions.second)
        {
            functions.second(key);
        }
    }

protected:
    void addStateKeyInputFunction(core::u32 const value,
                                  InputInState key_pressed_function,
                                  InputInState key_released_function)
    {
        p_->data_.reserve(value + 1U);
        while (p_->data_.size() < (value + 1U))
        {
            p_->data_.emplace_back();
        }
        p_->data_[value] = {core::move(key_pressed_function),
                            core::move(key_released_function)};
    }

    void setProcessingState(core::u32 const current_state)
    {
        p_->current_state_ = current_state;
    }

private:
    struct StatedInputComponentBasePrivate;
    core::PImplPointer<StatedInputComponentBasePrivate> p_;
};
}  // namespace haf::input
