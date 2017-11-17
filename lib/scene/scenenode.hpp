#pragma once

#ifndef LIB_DRAW_SCENENODE_HPP__
#define LIB_DRAW_SCENENODE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/vsp.hpp>
#include <lib/scene/transformable.hpp>
#include <lib/scene/hasname.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/scene/components/componentcontainer.hpp>

namespace lib
{
	namespace scene
	{
		class IComponent;
		class Scene;
		class Renderizable;

		/** \brief Main class representing all SceneNodes from a Scene.
		* This class is that serves as main entry point in the hierarchy of the scene
		*/
		class SceneNode : public core::HasName, public Transformable, public ComponentContainer
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
			virtual void create() {}

			/**
			* This method is called just before completing the initialization
			*/
			virtual void configure() {}

			/**
			* Method to add a user defined renderizable
			* @params args Arguments to be passed to the constructor
			* @returns The created renderizable
			*/
			template <typename T, typename... Args>
			sptr<T> createRenderizable(Args&&... args)
			{
				auto result(msptr<T>(this, std::forward<Args>(args)...));
				addRenderizable(result);
				return result;
			}

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
			void removeRenderizable(sptr<Renderizable> element);
			void clearAll();
			void clearRenderizables();
			void clearSceneNodes();
			void clearNodes();

			void render(bool parentTransformationChanged);
			virtual void update() {}
			Property<bool> visible;

			virtual Scene *const parentScene() { return m_parent->parentScene(); }
			const Rectf32 &scenePerspective();

			inline SceneNode *parent() noexcept { return m_parent; }
			inline const SceneNode *parent() const noexcept { return m_parent; }

			template <typename T>
			constexpr T *const snCast() { return dynamic_cast<T *const>(this); }

			template <typename T>
			constexpr const T *const snCast() const { return dynamic_cast<const T *const>(this); }

			template <typename T>
			constexpr void for_each_node_as(function<void(const sptr<T> &)> action)
			{
				for_each_node([&action](const sptr<Renderizable>&node) {
					if (auto tnode = std::dynamic_pointer_cast<T>(node)) {
						action(tnode);
					}
				});
			}

			template <typename T>
			constexpr void setNodeProperty(const T data, function<void(const sptr<T> &)> action)
			{
				for_each_node([&action](const sptr<Renderizable>&node) {
					if (auto tnode = std::dynamic_pointer_cast<NodeText>(node)) {
						action(tnode);
					}
				});
			}

			void for_each_node(function<void(const sptr<Renderizable> &)> action) const;

			template <typename T>
			constexpr void for_each_group_as(function<void(const sptr<T> &)> action)
			{
				for_each_group([&action](const sptr<SceneNode>&node) {
					if (auto tnode = std::dynamic_pointer_cast<T>(node)) {
						action(tnode);
					}
				});
			}

			void for_each_group(function<void(const sptr<SceneNode> &)> action) const;

			inline void setNeedsUpdate() noexcept { m_needsUpdate = true; }
			inline bool needsUpdate() const noexcept { return m_needsUpdate; }
			inline void clearNeedsUpdate() noexcept { m_needsUpdate = false; }
		protected:

			const vsp_with_deferred_delete<Renderizable> &renderNodes() const noexcept { return m_renderNodes; }
			const vsp_with_deferred_delete<SceneNode> &sceneNodes() const noexcept { return m_groups; }

			void addRenderizable(sptr<Renderizable> newElement);
			void addSceneNode(sptr<SceneNode> node);

		private:

			void internalUpdate() {
				if (m_needsUpdate) {
					m_needsUpdate = false;
					update();
				}
			}

			vsp_with_deferred_delete<Renderizable> m_renderNodes;
			vsp_with_deferred_delete<SceneNode> m_groups;

			void updateRemoves();

			SceneNode *m_parent{ nullptr };
			bool m_visible{ true };
			bool m_needsUpdate{ true };
		};

		using SceneNodeSPtr = sptr<SceneNode>;
	}
}

#endif
