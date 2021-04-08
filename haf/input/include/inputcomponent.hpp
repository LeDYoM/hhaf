#ifndef HAF_COMPONENT_INPUT_INCLUDE_HPP
#define HAF_COMPONENT_INPUT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/connection.hpp>
#include <haf/input/include/input_component_base.hpp>
#include <haf/input/include/key.hpp>

namespace haf::input
{
class InputComponent : public InputComponentBase
{
public:
    InputComponent();
    ~InputComponent() override;

    void update() override;

    htps::emitter<const Key&> KeyPressed;
    htps::emitter<const Key&> KeyReleased;
};
}  // namespace haf::input

#endif
