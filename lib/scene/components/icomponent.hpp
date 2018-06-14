#pragma once

#ifndef LIB_SCENE_ICOMPONENT_INCLUDE_HPP__
#define LIB_SCENE_ICOMPONENT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>

namespace lib::scene
{
    class SceneNode;

    /**
    * Base class for all components attached to a scene node.
    */
    class IComponent
    {
    public:
        /**
        * Interface to be implemented to update the component
        */
        virtual void update() {}

        /**
        * Destructor
        */
        virtual ~IComponent() {}

        /**
        * Method called after the component is attached to a node.
        * Override it to perform initialization
        */
        virtual void onAttached() {}

        /**
        * Shortcut method to cast to another scenenode type
        */
        template <typename T>
        inline T*const attachedNodeAs() const { return dynamic_cast<T*>(m_sceneNode); }

        inline const SceneNode *const attachedNode() const noexcept { return m_sceneNode; }
        inline SceneNode *const attachedNode() noexcept { return m_sceneNode; }

    private:
        SceneNode *m_sceneNode;
        friend class ComponentContainer;
    };

    template <typename T1, typename T2>
    class IComponentMixin : public IComponent
    {
        virtual void update() override
        {
            T1::update();
            T2::update();
        }
    };
}

#endif
