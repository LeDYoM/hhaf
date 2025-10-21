HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_RENDER_CONTEXT_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_CONTEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene/matrix4x4.hpp>

namespace haf::scene
{
struct SceneRenderContext
{
    [[nodiscard]] bool parentTransformationChanged() const noexcept
    {
        return m_parentTransformationChanged;
    }

    void setParentTransformationChanged(bool const nv) noexcept
    {
        m_parentTransformationChanged = nv;
    }

    [[nodiscard]] Matrix4x4 const& currentTransformation() const noexcept
    {
        return m_currentTransformation;
    }

    void setCurrentTransformation(Matrix4x4 const& nv) noexcept
    {
        m_currentTransformation = nv;
    }

    void reset()
    {
        *this = SceneRenderContext{};
    }

private:
    bool m_parentTransformationChanged{false};
    Matrix4x4 m_currentTransformation{Matrix4x4::Identity};

};

}  // namespace haf::scene

#endif
