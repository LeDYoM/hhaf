HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_INPUT_INCLUDE_HPP
#define HAF_COMPONENT_INPUT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/input/input_component_base.hpp>
#include <haf/include/input/key.hpp>

namespace haf::input
{
class InputComponent : public InputComponentBase
{
public:
    InputComponent();
    ~InputComponent() override;

    void update() override;

    evt::emitter<const Key&> KeyPressed;
    evt::emitter<const Key&> KeyReleased;
};
}  // namespace haf::input

#endif
