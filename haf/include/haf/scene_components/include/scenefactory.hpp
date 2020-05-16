#pragma once

#ifndef HAF_SCENE_SCENE_FACTORY_INCLUDE_HPP
#define HAF_SCENE_SCENE_FACTORY_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <haf/system/include/idatawrapper.hpp>

namespace haf::scene
{
class SceneFactory : public sys::IDataWrapper
{
public:
    bool registerSceneType(const mtps::str& name);

    template <typename T>
    bool registerSceneType()
    {
        return registerSceneType(T::StaticTypeName);
    }
};

} // namespace haf::scene

#endif
