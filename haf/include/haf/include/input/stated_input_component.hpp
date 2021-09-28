#ifndef HAF_STATED_INPUT_COMPONENT_INCLUDE_HPP
#define HAF_STATED_INPUT_COMPONENT_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/input/input_component_base.hpp>
#include <htypes/include/connection.hpp>
#include <haf/include/input/key.hpp>

namespace haf::input
{
class StatedInputComponent : public InputComponentBase
{
public:
    StatedInputComponent();
    ~StatedInputComponent() override;

    void update() override;

    htps::emitter<const Key&> KeyPressed;
    htps::emitter<const Key&> KeyReleased;
};
}  // namespace haf::input

#endif
