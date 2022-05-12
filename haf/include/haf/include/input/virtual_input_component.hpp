HTPS_PRAGMA_ONCE
#ifndef HAF_VIRTUAL_INPUT_COMPONENT_INCLUDE_HPP
#define HAF_VIRTUAL_INPUT_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/input/input_component_base.hpp>
#include <haf/include/input/key.hpp>

namespace haf::input
{
class VirtualInputComponent : public InputComponentBase
{
public:
    VirtualInputComponent();
    ~VirtualInputComponent() override;

    void update() override;

private:
    virtual void onKeyPressed(Key const&) {}
    virtual void onKeyReleased(Key const&) {}
};
}  // namespace haf::input

#endif
