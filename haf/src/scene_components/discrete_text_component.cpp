#include <haf/include/scene_components/discrete_text_component.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_components/text.hpp>

using namespace htps;

namespace haf::scene
{
void DiscreteTextComponent::incrementIndex() noexcept
{
    if (index() < (data().size() - 1))
    {
        index = index() + 1;
    }
    else
    {
        if (circleAroud())
        {
            index = 0;
        }
    }
}

void DiscreteTextComponent::decrementIndex() noexcept
{
    _setText(data()[index()]);

    if (index() > 0)
    {
        index = index() - 1;
    }
    else
    {
        if (circleAroud())
        {
            index = (data().size() - 1);
        }
    }
}

void DiscreteTextComponent::update()
{
    if (ps_readResetHasAnyChanged(index))
    {
        _setText((data().empty() || index() >= data().size())
                     ? ""
                     : data()[index()]);
    }
}

void DiscreteTextComponent::_setText(str const& nText)
{
    if (auto has_text{attachedNode()->componentOfType<Text>()})
    {
        has_text->Text = nText;
    }
}
}  // namespace haf::scene
