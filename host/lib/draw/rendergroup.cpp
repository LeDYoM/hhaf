#include "rendergroup.hpp"
#include "renderizable.hpp"
#include "nodeshape.hpp"
#include "nodequad.hpp"
#include "nodetext.hpp"
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

		RenderGroup::~RenderGroup()
		{
			m_renderNodes.clear();
		}

		sptr<NodeText> RenderGroup::createText(const std::string &name, const std::string& string, sptr<Font> font, u32 characterSize, const Color &color)
		{
			auto result = msptr<NodeText>(name,string,font,characterSize,color);
			addRenderizable(result);
			return result;
		}

		sptr<NodeShape> RenderGroup::createShape(const std::string &name, const vector2df &size, sptr<Texture> texture, u32 pointCount, const Color &color)
		{
			auto result = msptr<NodeShape>(name,size,texture,pointCount,color);
			addRenderizable(result);
			return result;
		}

		sptr<NodeQuad> RenderGroup::createSpriteShape(const std::string &name, const vector2df &size, sptr<Texture> texture, const Color &color)
		{
			auto result = msptr<NodeQuad>(name,size,texture,color);
			addRenderizable(result);
			return result;
		}

		sptr<draw::Renderizable> RenderGroup::addRenderizable(sptr<Renderizable> newElement)
		{
			m_renderNodes.emplace_back(newElement);
			return newElement;
		}

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
