HTPS_PRAGMA_ONCE
#ifndef HAF_RENDERIZABLE_COMPONENT_INCLUDE_HPP
#define HAF_RENDERIZABLE_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/scene_components/renderizables.hpp>

namespace haf::render
{
class Renderizable;
}

namespace haf::scene
{
class Renderizable : public Renderizables
{
    using BaseClass = Renderizables;

public:
    htps::sptr<render::Renderizable> const& node() const noexcept;
};
}  // namespace haf::scene

#endif
