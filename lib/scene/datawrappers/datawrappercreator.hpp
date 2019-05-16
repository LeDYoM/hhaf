#pragma once

#ifndef LIB_SCENE_DATA_WRAPPER_CREATOR_INCLUDE_HPP
#define LIB_SCENE_DATA_WRAPPER_CREATOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include "idatawrapper.hpp"

namespace lib::scene
{
    class SceneNode;

    /**
    */
    class DataWrapperCreator
    {
    public:
        constexpr DataWrapperCreator(SceneNode *const scene_node) noexcept
            : scene_node_{scene_node} {}

        ~DataWrapperCreator() {}

        template <typename T>
        uptr<T> dataWrapper()
        {
            uptr<T> result = muptr<T>();
            result->scene_node_ = scene_node_;
            result->onCreated();
            return result;
        }
    private:
        SceneNode* const scene_node_;
    };
}

#endif
