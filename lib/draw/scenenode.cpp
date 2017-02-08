#include "scenenode.hpp"
#include "renderizable.hpp"
#include "scene.hpp"
#include "animationcomponent.hpp"
#include "ianimation.hpp"

#include <lib/core/window.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		SceneNode::SceneNode(const std::string &name, SceneNode *parent)
			: core::HasName{ name }, m_parent{ parent } {	}

		SceneNode::~SceneNode() = default;

		bool SceneNode::removeRenderizable(const sptr<Renderizable> &element)
		{
			return removespFrom(m_renderNodes, element);
		}

		void SceneNode::draw()
		{
			if (name() == "cursorNode")
			{
				int b = 1;
			}
			if (isVisible()) {
				auto handle(host().rStates().pushChanges(&getTransform(), nullptr));

				for (const auto& renderizable : m_renderNodes) {
					renderizable->draw();
				}

				for (const auto& group : m_groups) {
					group->draw();
				}
			}
		}

		void SceneNode::addAnimation(sptr<anim::IAnimation> nanimation, sptr<SceneNode> tracker) noexcept
		{
			parentScene()->createAnimation(std::move(nanimation), std::move(tracker));
		}

		Rectf32 SceneNode::scenePerspective()
		{
			return parentScene()->getView()->perspective();
		}

		void SceneNode::setColor(const Color & color, const bool applySceneNodes, const u32 deepLevel)
		{
			for (auto &node : m_renderNodes) {
				node->color = color;
			}

			if (applySceneNodes && deepLevel > 0) {
				for (auto &sNode : m_groups) {
					sNode->setColor(color,true,deepLevel-1);
				}
			}
		}

		sptr<SceneNode> SceneNode::createSceneNode(const std::string & name)
		{
			sptr<SceneNode> rg = std::make_shared<SceneNode>(name, this);
			addSceneNode(rg);
			return rg;
		}

		bool SceneNode::moveLastBeforeNode(const sptr<SceneNode> &beforeNode)
		{
			__ASSERT(!m_groups.empty(), "Cannot moveLastInsertedBeforeNode on empty container");
			if (!beforeNode) return false;

			// Find the node to swap before to
			auto iterator (std::find(m_groups.begin(), m_groups.end(),beforeNode));

			// If beforeNode not found, nothing to do
			if (iterator == m_groups.end()) return false;

			// If beforeNode is the last element, nothing to do
			if (iterator == std::prev(m_groups.end())) return false;

			auto last(std::prev(m_groups.end()));

			// Do not swap yourself
			if (*iterator == *last) return false;

			// Swap the iterators
			std::swap(*iterator, *last);
			return true;
		}

		void SceneNode::addRenderizable(const sptr<Renderizable> &newElement)
		{
			m_renderNodes.push_back(newElement);
		}

		void SceneNode::addSceneNode(const sptr<SceneNode> &node)
		{
			m_groups.push_back(node);
			node->m_parent = this;
			node->onAddedToScene();
		}

		bool SceneNode::removeSceneNode(sptr<SceneNode> element)
		{
			return removespFrom(m_groups, element);
		}

		void SceneNode::clear()
		{
			m_groups.clear();
			m_renderNodes.clear();
		}
	}
}
