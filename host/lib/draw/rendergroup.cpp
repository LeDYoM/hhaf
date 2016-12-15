#include "rendergroup.hpp"
#include "renderizable.hpp"
#include "scene.hpp"

#include <lib/core/window.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		RenderGroup::RenderGroup(const std::string &name, RenderGroup *parent)
			: HasName{ name }, m_parent{ parent }
		{
		}

		RenderGroup::~RenderGroup() = default;

		bool RenderGroup::removeRenderizable(sptr<Renderizable> element)
		{
			return removeFromspVector(element, m_renderNodes);
		}

		void RenderGroup::draw()
		{
			if (isVisible()) {
				updateAnimations();
				auto handle = host().rStates().pushChanges(&getTransform(), nullptr);

				for (const auto& renderizable : m_renderNodes) {
					renderizable->draw();
				}
			}
		}

		sptr<RenderGroup> RenderGroup::createNewRenderGroup(const std::string & name, sptr<IDrawable> beforeNode)
		{
			sptr<RenderGroup> rg = std::make_shared<RenderGroup>(name, this);
			addRenderGroup(rg, beforeNode);
			return rg;
		}

		void RenderGroup::addRenderGroup(sptr<RenderGroup> node, sptr<IDrawable> beforeNode)
		{
			if (!beforeNode) {
				m_renderNodes.emplace_back(node);
			}
			else {
				for (auto iterator = m_renderNodes.begin(); iterator != m_renderNodes.end();++iterator) {
					if (*iterator == beforeNode) {
						m_renderNodes.emplace(iterator, node);
						break;
					}
				}
			}
			node->m_parent = this;
			node->onAddedToScene();
		}

		bool RenderGroup::removeRenderGroup(sptr<RenderGroup> element)
		{
			return removeFromspVector(element, m_renderNodes);
		}

		void RenderGroup::clear()
		{
			m_renderNodes.clear();
		}
	}
}
