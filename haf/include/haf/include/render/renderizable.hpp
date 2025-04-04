HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_RENDERIZABLE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/properties/property_state.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/p_impl_pointer.hpp>

#include <haf/include/scene/color.hpp>
#include <haf/include/render/renderizable_data.hpp>
#include <haf/include/scene/hasname.hpp>
#include <haf/include/render/fig_type.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include <haf/include/render/renderizable_data.hpp>
#include <haf/include/scene/material.hpp>
#include <haf/include/scene/scene_node.hpp>

namespace haf::render
{
class Renderizable final : public sys::HasName
{
public:
    Renderizable(htps::rptr<scene::SceneNode> parent,
                 RenderizableData&& renderizable_data);

    ~Renderizable();

    scene::Material& material() noexcept { return m_material; }
    scene::Material const& material() const noexcept { return m_material; }

    void render(bool const parent_transformation_changed);

    prop::BasicProperty<bool> visible{true};

    htps::rptr<scene::SceneNode> parent() noexcept;
    htps::rptr<scene::SceneNode const> parent() const noexcept;

private:
    scene::Material m_material;
    htps::rptr<scene::SceneNode> parent_;
    struct RenderizablePrivate;
    htps::PImplPointer<RenderizablePrivate> p_;

    void update(bool const parent_transformation_changed);
};
}  // namespace haf::render

#endif
