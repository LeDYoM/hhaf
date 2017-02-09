#ifndef LIB_DRAW_SCENENODE_HPP__
#define LIB_DRAW_SCENENODE_HPP__

#pragma once

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "transformable.hpp"
#include "nodeshape.hpp"
#include "nodequad.hpp"
#include "nodetext.hpp"

namespace lib
{
	namespace core
	{
		class Window;
	}
	namespace draw
	{
		namespace anim
		{
			class IAnimation;
		}

		class Scene;
		class Renderizable;
		class SceneNode : public core::HasName, public Transformable
		{
		public:
			SceneNode(SceneNode *parent, std::string name);
			virtual ~SceneNode();

			virtual void onAddedToScene() {}

			/**
			* Method to add a user defined renderizable
			* @params args Arguments to be passed to the constructor
			* @returns The created renderizable
			*/
			template <typename T, typename... Args>
			sptr<T> createRenderizable(Args&&... args)
			{
				auto result(msptr<T>(std::forward<Args>(args)...));
				addRenderizable(result);
				return result;
			}

			bool removeRenderizable(const sptr<Renderizable> &element);
			void clear();

			template <typename T = SceneNode, typename... Args>
			sptr<T> createSceneNode(std::string name, Args&&... args)
			{
				auto result(msptr<T>(this, std::move(name), std::forward<Args>(args)...));
				addSceneNode(result);
				return result;
			}

			template <typename T, typename... Args>
			std::pair<sptr<SceneNode>,sptr<T>> createSceneNodeWidthRenderizable(str_const name, Args&&... args)
			{
				auto result(createSceneNode<SceneNode>(name));
				auto result2(result->createRenderizable<T>(name + "_node", std::forward<Args>(args)...));
				return{ result,result2 };
			}

			bool moveLastBeforeNode(const sptr<SceneNode> &beforeNode);
			bool removeSceneNode(sptr<SceneNode> element);

			void draw();
			void addAnimation(sptr<anim::IAnimation> nanimation, sptr<SceneNode> tracker = {}) noexcept;

			inline bool isVisible() const noexcept { return m_visible; }
			inline void setVisible(bool nv) noexcept { m_visible = nv; }

			virtual Scene *const parentScene() { return m_parent->parentScene(); }
			Rectf32 scenePerspective();

			/**
			* Set a color for all vertex for all child nodes of this node
			* @param [in] color to be set
			* @param [in] apply the function to scenenodes too
			* @
			*/
			void setColor(const Color &color, const bool applySceneNodes = true, const u32 deepLevel = {});

		protected:

			inline SceneNode *parent() const noexcept { return m_parent; }
			void addRenderizable(const sptr<Renderizable> &newElement);
			void addSceneNode(const sptr<SceneNode> &node);

		private:

			vector_shared_pointers<Renderizable> m_renderNodes;
			vector_shared_pointers<SceneNode> m_groups;

			SceneNode *m_parent{ nullptr };
			bool m_visible{ true };

		};

		template <typename T, typename... Args >
		class SceneNodeRenderizable : public SceneNode
		{
		public:
			SceneNodeRenderizable(const std::string &name, SceneNode *parent, Args&&... args) : SceneNode(name, parent)
			{
				m_node = createRenderizable<T>(name, std::forward<Args>(args)...);
			}

			sptr<T> m_node;
		};

		using SceneNodeSPtr = sptr<SceneNode>;
	}
}

#endif
