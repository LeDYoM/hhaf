#ifndef __LIB_RENDERGROUP_HPP__
#define __LIB_RENDERGROUP_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "scenenode.hpp"
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
			SceneNode(const std::string &name, SceneNode *parent = nullptr);
			virtual ~SceneNode();

			virtual void onAddedToScene() {}

			template <typename T, typename... Args>
			sptr<T> createRenderizable(Args&&... args)
			{
				auto result(msptr<T>(std::forward<Args>(args)...));
				m_renderNodes.push_back(result);
				return result;
			}

			bool removeRenderizable(const sptr<Renderizable> &element);
			void clear();

			sptr<SceneNode> createNewRenderGroup(const std::string &name,sptr<SceneNode> beforeNode=nullptr);
			bool removeRenderGroup(sptr<SceneNode> element);

			void draw();
			void addAnimation(sptr<anim::IAnimation> nanimation, sptr<SceneNode> tracker = {}) noexcept;

			inline bool isVisible() const noexcept { return m_visible; }
			inline void setVisible(bool nv) noexcept { m_visible = nv; }

		protected:

			template <typename T>
			sptr<T> addRenderizable(sptr<T> newElement)
			{
				m_renderNodes.push_back(newElement);
				return newElement;
			}

			void addRenderGroup(sptr<SceneNode> node, const sptr<SceneNode> beforeNode = nullptr);

			inline SceneNode *parent() const noexcept { return m_parent; }

			virtual Scene *const parentScene() { return m_parent->parentScene(); }

			vector_shared_pointers<Renderizable> m_renderNodes;
			vector_shared_pointers<SceneNode> m_groups;

		private:
			SceneNode *m_parent{ nullptr };
			bool m_visible{ true };

		};

		template <class T>
		class TransformableNode : public SceneNode
		{
		public:
			T m_node;

			using T::T;
			operator T() { return m_node; }
		};

	}
}

#endif
