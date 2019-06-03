#pragma once

#ifndef LIB_SCENE_SCENENODE_INCLUDE_HPP
#define LIB_SCENE_SCENENODE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/transformable.hpp>
#include <lib/scene/hasname.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/scene/components/componentcontainer.hpp>
#include <lib/scene/datawrappers/datawrappercreator.hpp>

#include "scenenodeblob.hpp"

namespace lib::scene
{
    class Renderizable;
    class IComponent;
    class Scene;

    /** \brief Main class representing all SceneNodes from a Scene.
    * This class is that serves as main entry point in the hierarchy of the scene
    */
    class SceneNode : public core::HasName, public Transformable, 
        public DataWrapperCreator, public ComponentContainer, public SceneNodeBlob
    {
    public:
        SceneNode(const SceneNode&) = delete;
        SceneNode &operator=(const SceneNode&) = delete;

        SceneNode(SceneNode *const parent, str name);
        virtual ~SceneNode();

        /**
        * Method called when adding a new node just after creation.
        * Override it to add code on creation
        * @see configure
        */
        virtual void onCreated() {}

        /**
        * This method is called just before completing the initialization
        */
        virtual void configure() {}

        template <typename T = SceneNode, typename... Args>
        sptr<T> createSceneNode(Args&&... args)
        {
            auto result(msptr<T>(this, std::forward<Args>(args)...));
            addSceneNode(result);
            return result;
        }

        sptr<SceneNode> createSceneNode(str name)
        {
            return createSceneNode<SceneNode>(std::move(name));
        }

        bool moveLastBeforeNode(const sptr<SceneNode> &beforeNode);
        void removeSceneNode(sptr<SceneNode> element);
        void clearAll();
        void clearSceneNodes();

        void render(bool parentTransformationChanged);
        virtual void update() {}

        virtual Scene *const parentScene() noexcept { return m_parent->parentScene(); }
        virtual const Scene *const parentScene() const noexcept { return m_parent->parentScene(); }

        template <typename SceneType>
        SceneType *const parentSceneAs() { return dynamic_cast<SceneType*>(parentScene()); }

        template <typename SceneType>
        const SceneType *const parentSceneAs() const { return dynamic_cast<SceneType*>(parentScene()); }

        inline SceneNode *parent() noexcept { return m_parent; }
        inline const SceneNode *parent() const noexcept { return m_parent; }

        template <typename T>
        constexpr T *const snCast() { return dynamic_cast<T *const>(this); }

        template <typename T>
        constexpr const T *const snCast() const { return dynamic_cast<const T *const>(this); }

        BasicProperty<bool> visible;

        constexpr const auto &sceneNodes() const noexcept { return m_groups; }
        constexpr auto &sceneNodes() noexcept { return m_groups; }
        constexpr auto sceneNodesSize() const noexcept { return sceneNodes().size(); }

        // TODO: Temporary
        vector<sptr<Renderizable>> m_renderNodes;

    protected:

        void addSceneNode(sptr<SceneNode> node);

    private:
        friend class SceneNodeBlob;
        SceneNode *m_parent;

        vector<sptr<SceneNode>> m_groups;
    };

    using SceneNodeSPtr = sptr<SceneNode>;
}

#endif
