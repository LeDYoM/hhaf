#include "scenenode.hpp"
#include "renderizable.hpp"
#include "scene.hpp"
#include "icomponent.hpp"

#include <lib/core/window.hpp>
#include <lib/core/host.hpp>
#include <lib/core/log.hpp>
#include <lib/draw/renderstatesstack.hpp>

namespace lib
{
	namespace draw
	{
		SceneNode::SceneNode(SceneNode *const parent, str_const name)
			: core::HasName{ std::move(name) }, ComponentContainer{ this }, m_parent{ parent }, visible{ true } {}

		SceneNode::~SceneNode() { clear(); };

		void SceneNode::draw()
		{
			if (visible()) {
				// Update the node components
				updateComponents();

				const auto handle(host().rStates().pushChanges(&transform(), nullptr));

				for (const auto& renderizable : m_renderNodes.nodes) {
					renderizable->draw();
				}

				for (const auto& group : m_groups.nodes) {
					group->draw();
				}

				updateRemoves();
			}
		}

		const Rectf32 &SceneNode::scenePerspective()
		{
			return parentScene()->viewRect();
		}

		void SceneNode::setColor(const Color & color, const bool applySceneNodes)
		{
			for (auto &node : m_renderNodes.nodes) {
				node->color = color;
			}

			if (applySceneNodes) {
				for (auto &sNode : m_groups.nodes) {
					sNode->setColor(color,true);
				}
			}
		}

		bool SceneNode::moveLastBeforeNode(const sptr<SceneNode> &beforeNode)
		{
			__ASSERT(!m_groups.nodes.empty(), "Cannot moveLastInsertedBeforeNode on empty container");
			if (!beforeNode) return false;

			// Find the node to swap before to
			auto iterator (std::find(m_groups.nodes.begin(), m_groups.nodes.end(),beforeNode));

			// If beforeNode not found, nothing to do
			if (iterator == m_groups.nodes.end()) return false;

			// If beforeNode is the last element, nothing to do
			if (iterator == std::prev(m_groups.nodes.end())) return false;

			auto last(std::prev(m_groups.nodes.end()));

			// Do not swap yourself
			if (*iterator == *last) return false;

			// Swap the iterators
			std::swap(*iterator, *last);
			return true;
		}

		void SceneNode::for_each_node(std::function<void(const sptr<Renderizable>&)> action)
		{
			std::for_each(m_renderNodes.nodes.cbegin(), m_renderNodes.nodes.cend(), action);
		}

		void SceneNode::for_each_group(std::function<void(const sptr<SceneNode>&)> action)
		{
			std::for_each(m_groups.nodes.cbegin(), m_groups.nodes.cend(), action);
		}

		void SceneNode::addRenderizable(const sptr<Renderizable> &newElement)
		{
			m_renderNodes.nodes.push_back(newElement);
		}

		void SceneNode::addSceneNode(sptr<SceneNode> node)
		{
			m_groups.nodes.push_back(node);
			node->m_parent = this;
			node->create();
		}

		void SceneNode::updateRemoves()
		{
			m_groups.deferred_remove();
			m_renderNodes.deferred_remove();
		}

		void SceneNode::removeSceneNode(const sptr<SceneNode> &element)
		{
			__ASSERT(this != element.get(), "Cannot delete myself from myself");
			m_groups.m_nodesToDelete.push_back(element);
		}

		void SceneNode::removeRenderizable(const sptr<Renderizable> &element)
		{
			m_renderNodes.m_nodesToDelete.push_back(element);
		}

		void SceneNode::clear()
		{
			m_groups.nodes.clear();
			m_renderNodes.nodes.clear();
			clearComponents();
		}
	}
}
