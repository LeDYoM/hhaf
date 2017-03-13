#include "scenenode.hpp"
#include "renderizable.hpp"
#include "scene.hpp"
#include "icomponent.hpp"

#include <lib/core/window.hpp>
#include <lib/core/host.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		SceneNode::SceneNode(SceneNode *parent, str_const&& name)
			: core::HasName{ std::move(name) }, ComponentContainer{ this }, m_parent{ parent }, visible{ true } {}

		SceneNode::~SceneNode() = default;

		bool SceneNode::removeRenderizable(const sptr<Renderizable> &element)
		{
			return removespFrom(m_renderNodes, element);
		}

		void SceneNode::draw()
		{
			if (visible()) {
				// Update the node components
				updateComponents();

				auto handle(host().rStates().pushChanges(&transform(), nullptr));

				for (const auto& renderizable : m_renderNodes) {
					renderizable->draw();
				}

				for (const auto& group : m_groups) {
					group->draw();
				}
			}
		}

		Rectf32 SceneNode::scenePerspective()
		{
			return parentScene()->getView()->perspective();
		}

		void SceneNode::setColor(const Color & color, const bool applySceneNodes)
		{
			for (auto &node : m_renderNodes) {
				node->color = color;
			}

			if (applySceneNodes) {
				for (auto &sNode : m_groups) {
					sNode->setColor(color,true);
				}
			}
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

		void SceneNode::addSceneNode(sptr<SceneNode> node)
		{
			m_groups.push_back(node);
			node->m_parent = this;
			node->create();
		}

		bool SceneNode::removeSceneNode(const sptr<SceneNode> &element)
		{
			__ASSERT(this != element.get(), "Cannot delete myself from myself");
			return removespFrom(m_groups, element);
		}

		void SceneNode::clear()
		{
			m_groups.clear();
			m_renderNodes.clear();
			clearComponents();
		}
	}
}
