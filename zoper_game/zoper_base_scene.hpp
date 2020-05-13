#pragma once

#ifndef ZOPER_BASE_SCENE_INCLUDE_HPP
#define ZOPER_BASE_SCENE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <haf/scene/include/scene.hpp>

namespace zoper
{
class ZoperBaseScene final : public haf::scene::Scene
{
public:
    ZoperBaseScene(mtps::str scene_name);
    ~ZoperBaseScene() override;

    void onCreated() override;

protected:
    using BaseClass = haf::scene::Scene;
};

} // namespace zoper

#endif
