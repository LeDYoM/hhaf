#include <haf/include/scene_components/discretetextcomponent.hpp>
#include <haf/include/scene_nodes/scenenodetext_properties.hpp>

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
        _setText(data()[index()]);
    }
}

void DiscreteTextComponent::_setText(str const& nText)
{
    using namespace nodes;
    attachedNode()->prop<SceneNodeTextProperties>().set<Text>(nText);
}
}  // namespace haf::scene
