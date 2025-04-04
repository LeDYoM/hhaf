#include <haf/include/scene_components/renderizable.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/scene_node.hpp>

using namespace htps;

namespace haf::scene
{
sptr<render::Renderizable> const& Renderizable::node() const noexcept
{
    LogAsserter::log_assert(!BaseClass::emptyRenderizables(),
                            "The Renderizables vector is empty");
    return BaseClass::operator[](0U);
}
}  // namespace haf::scene
