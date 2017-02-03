#include "rendergroup.hpp"
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
		RenderGroup::RenderGroup(const std::string &name, RenderGroup *parent)
			: SceneNode{ name }, m_parent{ parent } {	}

		RenderGroup::~RenderGroup() = default;

		bool RenderGroup::removeRenderizable(const sptr<Renderizable> &element)
		{
			return removespFrom(m_renderNodes, element);
		}

		void RenderGroup::draw()
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

		void RenderGroup::addAnimation(sptr<anim::IAnimation> nanimation, sptr<SceneNode> tracker) noexcept
		{
			parentScene()->createAnimation(std::move(nanimation), std::move(tracker));
		}

		sptr<RenderGroup> RenderGroup::createNewRenderGroup(const std::string & name, sptr<RenderGroup> beforeNode)
		{
			sptr<RenderGroup> rg = std::make_shared<RenderGroup>(name, this);
			addRenderGroup(rg, beforeNode);
			return rg;
		}

		void RenderGroup::addRenderGroup(sptr<RenderGroup> node, const sptr<RenderGroup> beforeNode)
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

		bool RenderGroup::removeRenderGroup(sptr<RenderGroup> element)
		{
			return removespFrom(m_groups, element);
		}

		void RenderGroup::clear()
		{
			m_groups.clear();
			m_renderNodes.clear();
		}
	}
}
