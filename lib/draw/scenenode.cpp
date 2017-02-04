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

		sptr<SceneNode> SceneNode::createNewRenderGroup(const std::string & name, sptr<SceneNode> beforeNode)
		{
			sptr<SceneNode> rg = std::make_shared<SceneNode>(name, this);
			addRenderGroup(rg, beforeNode);
			return rg;
		}

		void SceneNode::addRenderGroup(sptr<SceneNode> node, const sptr<SceneNode> beforeNode)
		{
			if (!beforeNode) {
				m_groups.emplace_back(node);
			}
			else {
				for (auto iterator = m_groups.cbegin(); iterator != m_groups.cend();++iterator) {
					if (*iterator == beforeNode) {
						m_groups.emplace(iterator, node);
						break;
					}
				}
			}
			node->m_parent = this;
			node->onAddedToScene();
		}

		bool SceneNode::removeRenderGroup(sptr<SceneNode> element)
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
