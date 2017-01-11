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
			: HasName{ name }, m_parent{ parent } {	}

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
			}
		}

		sptr<RenderGroup> RenderGroup::createNewRenderGroup(const std::string & name, sptr<IDrawable> beforeNode)
		{
			sptr<RenderGroup> rg = std::make_shared<RenderGroup>(name, this);
			addRenderGroup(rg, beforeNode);
			return rg;
		}

		void RenderGroup::addRenderGroup(sptr<RenderGroup> node, const sptr<IDrawable> beforeNode)
		{
			if (!beforeNode) {
				m_renderNodes.emplace_back(node);
			}
			else {
				for (auto iterator = m_renderNodes.cbegin(); iterator != m_renderNodes.cend();++iterator) {
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
			return removespFrom(m_renderNodes, element);
		}

		void RenderGroup::clear()
		{
			m_renderNodes.clear();
		}
	}
}
