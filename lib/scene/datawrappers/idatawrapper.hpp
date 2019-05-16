#pragma once

#ifndef LIB_SCENE_IDATA_WRAPPER_INCLUDE_HPP
#define LIB_SCENE_IDATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::scene
{
    class SceneNode;

    /**
	* Base class for classes that provide some kind of access to specific data.
	* The idea is that when an scene node needs access to specific data it wraps
	* it in some subclass of this class that will bring getters and setter to
	* some specific data via a scene node.
    */
    class IDataWrapper
    {
    public:

        /**
        * Destructor
        */
        virtual ~IDataWrapper() {}

        /**
        * Method called after the component is attached to a node.
        * Override it to perform initialization
        */
        virtual void onCreated() {}

        /**
        * Shortcut method to cast to another scenenode type
        */
        template <typename T>
        inline T*const attachedNodeAs() const { return dynamic_cast<T*>(scene_node_); }

        constexpr const SceneNode *const attachedNode() const noexcept { return scene_node_; }
        constexpr SceneNode *const attachedNode() noexcept { return scene_node_; }

    private:
        SceneNode* scene_node_;
        friend class DataWrapperCreator;
    };
}

#endif
