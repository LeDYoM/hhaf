#ifndef HAF_CONSOLE_INCLUDE_HPP
#define HAF_CONSOLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene/transformable_scenenode.hpp>

namespace zoper
{
class Console : public haf::scene::TransformableSceneNode
{
    using BaseClass = haf::scene::TransformableSceneNode;

public:
    using BaseClass::BaseClass;

    void onCreated() override;
};
}  // namespace zoper

#endif