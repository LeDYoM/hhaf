#include "rendergroup.hpp"
#include "renderizable.hpp"
#include "nodeshape.hpp"
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
			_renderNodes.clear();
		}

		sptr<NodeText> RenderGroup::createText(const std::string &name)
		{
			auto result = sptr<NodeText>(new NodeText(name));
			addRenderizable(result);
			return result;
		}

		sptr<NodeShape> RenderGroup::createShape(const std::string &name, const vector2df &radius/*=vector2df()*/, u32 pointCount/*=30*/)
		{
			auto result = sptr<NodeShape>(new NodeShape(name,radius,pointCount));
			addRenderizable(result);
			return result;
		}

		sptr<NodeShape> RenderGroup::createSpriteShape(const std::string &name, const vector2df &radius /*= vector2df()*/)
		{
			auto result = sptr<NodeShape>(new NodeShape(name,radius, 4,NodeShape::NodeMode::Sprite));
			addRenderizable(result);
			return result;
		}

		sptr<draw::Renderizable> RenderGroup::addRenderizable(sptr<Renderizable> newElement)
		{
			_renderNodes.push_back(newElement);
			return newElement;
		}

		bool RenderGroup::removeRenderizable(sptr<Renderizable> element)
		{
			return removeFromspVector(element, _renderNodes);
		}

		void RenderGroup::draw()
		{
			if (isVisible()) {
				updateAnimations();
				auto oldTransformation = host().rStates().internalStates().transform;
				host().rStates().internalStates().transform *= getTransform();

				for (const auto& renderizable : _renderNodes) {
					renderizable->draw();
				}
				host().rStates().internalStates().transform = std::move(oldTransformation);
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
				_renderNodes.push_back(node);
			}
			else {
				for (auto iterator = _renderNodes.begin(); iterator != _renderNodes.end();++iterator) {
					if (*iterator == beforeNode) {
						_renderNodes.insert(iterator, node);
						break;
					}
				}
			}
			node->m_parent = this;
			node->onAddedToScene();
		}

		bool RenderGroup::removeRenderGroup(sptr<RenderGroup> element)
		{
			return removeFromspVector(element, _renderNodes);
		}

		void RenderGroup::clear()
		{
			_renderNodes.clear();
		}
	}
}
