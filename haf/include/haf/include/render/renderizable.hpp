HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_RENDERIZABLE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/propertystate.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/p_impl_pointer.hpp>

#include <haf/include/scene/color.hpp>
#include <haf/include/render/renderizable_data.hpp>
#include <haf/include/scene/hasname.hpp>
#include <haf/include/render/fig_type.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include <haf/include/render/renderizable_data.hpp>
#include <haf/include/render/renderizable_object_data.hpp>

namespace haf::scene
{
class TransformableSceneNode;
}

namespace haf::render
{
class Renderizable final : public sys::HasName, private RenderizableObjectData
{
public:
    using RenderizableObjectData::prop;

    Renderizable(htps::rptr<scene::TransformableSceneNode> parent,
                 RenderizableData&& renderizable_data);

    ~Renderizable();

    void render(bool const parent_transformation_changed);

    htps::BasicProperty<bool> visible{true};

    htps::rptr<scene::TransformableSceneNode> parent() noexcept;
    htps::rptr<scene::TransformableSceneNode const> parent() const noexcept;

private:
    htps::rptr<scene::TransformableSceneNode> parent_;
    struct RenderizablePrivate;
    htps::PImplPointer<RenderizablePrivate> p_;

    void update(bool const parent_transformation_changed);
};
}  // namespace haf::render

#endif
