#include <haf/include/scene_components/transformation.hpp>
#include "render/geometry_math.hpp"

#include <cmath>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/iscene_render_context_provider.hpp>

namespace haf::scene
{
Transformation::Transformation() noexcept : transform_{}
{}

Transformation::~Transformation() = default;

bool Transformation::updateTransformIfNecessary() noexcept
{
    if (ps_readResetHasAnyChanged(Position, Scale, Rotation))
    {
        updateTransform();
        return true;
    }
    return false;
}

void Transformation::updateTransform()
{
    // Recompute the combined transform
    auto const angle{-Rotation() * render::ToRadians<Scalar>};
    VectorScalar const scale_cos{Scale() *
                                 static_cast<Scalar>(std::cos(angle))};
    VectorScalar const scale_sin{Scale() *
                                 static_cast<Scalar>(std::sin(angle))};
    VectorScalar const position{Position()};

    transform_ = {scale_cos.x,     scale_sin.y,     position.x,
                  -scale_sin.x,    scale_cos.y,     position.y,
                  Matrix4x4::Zero, Matrix4x4::Zero, Matrix4x4::One};
}

Matrix4x4 const& Transformation::matrix() const noexcept
{
    return transform_;
}

void Transformation::setLeftTopPositionScale(VectorScalar const& vector)
{
    Position = VectorScalar{-0.5F, -0.5F} + (vector / 2.0F);
    Scale    = vector;
}

void Transformation::setRightTopPositionScale(VectorScalar const& vector)
{
    VectorScalar origin{0.5F, -0.5F};
    origin.x -= vector.x / 2.0F;
    origin.y += vector.y / 2.0F;
    Position = htps::move(origin);
    Scale    = vector;
}

Matrix4x4 const& Transformation::globalTransform() const noexcept
{
    return global_transform_;
}

Matrix4x4 const& Transformation::localTransform() const noexcept
{
    return matrix();
}

void Transformation::update()
{
    //    HAF_PROFILE_SCENE_NODE_METHOD(prTime)

    auto const& transformable_parent{attachedNode()->parent()};
    auto& sceneRenderContext =
        attachedNode()
            ->subSystem<scene::ISceneRenderContextProvider>()
            ->sceneRenderContext();

    sceneRenderContext.currentTransformation = transformable_parent != nullptr
        ? transformable_parent->component<Transformation>()->globalTransform()
        : Matrix4x4::Identity;

    bool localTransformationChanged{updateTransformIfNecessary()};

    if (!localTransformationChanged)
    {
        localTransformationChanged =
            sceneRenderContext.parentTransformationChanged_;
    }

    if (localTransformationChanged)
    {
        global_transform_ = sceneRenderContext.currentTransformation * matrix();
    }

    sceneRenderContext.parentTransformationChanged_ =
        localTransformationChanged;
}

}  // namespace haf::scene
