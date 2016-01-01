#include "rendergroup.hpp"
#include "renderizable.hpp"
#include "../../core/window.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			RenderGroup::RenderGroup(const std::string &name, RenderGroup *parent)
				: HasName{ name }, _parent{ parent }
			{
			}


			RenderGroup::~RenderGroup()
			{
				_renderNodes.clear();
			}

			sptr<draw::Renderizable> RenderGroup::createText(const std::string &name)
			{
				auto result = sptr<draw::Renderizable>(new Renderizable(name, new sf::Text));
				addRenderizable(result);
				return result;
			}

			sptr<draw::Renderizable> RenderGroup::createShape(const std::string &name, const sf::Vector2f &radius/*=sf::Vector2f()*/, u32 pointCount/*=30*/)
			{
				auto result = sptr<draw::Renderizable>(new Renderizable(name, new NodeShape(radius,pointCount)));
				addRenderizable(result);
				return result;
			}

			sptr<draw::Renderizable> RenderGroup::createSpriteShape(const std::string &name, const sf::Vector2f &radius /*= sf::Vector2f()*/)
			{
				auto result = sptr<draw::Renderizable>(new Renderizable(name, new NodeShape(radius, 4,NodeShape::NodeMode::Sprite)));
				addRenderizable(result);
				return result;
			}

			sptr<draw::Renderizable> RenderGroup::addRenderizable(sptr<Renderizable> newElement)
			{
				_renderNodes.push_back(newElement);
				return newElement;
			}

			template <typename T,class Y>
			bool removeFromspVector(sptr<T> element,std::vector<sptr<Y>> &container)
			{
				auto i = container.begin();
				bool found = false;

				while (i != container.end() && !found)
				{
					T* tempElement = element.get();
					Y* tempContent = (*i).get();

					if ((*i).get() == element.get())
					{
						i = container.erase(i);
						found = true;
					}
					else
					{
						++i;
					}
				}

				LOG_ERROR("Element " << element << " not found in list");
				LOG_DEBUG("Element was" << (found ? "" : " not ") << " found. Number of left references: " << element.use_count());
				return found;
			}
			bool RenderGroup::removeRenderizable(sptr<Renderizable> element)
			{
				return removeFromspVector(element, _renderNodes);
			}

			u32 RenderGroup::draw(lib::core::Window *window, sf::RenderStates &states) const
			{
				if (isVisible())
				{
					u32 rNodes{ 0 };
					auto t = this->getTransform();
					states.transform *= t;

					for (const auto renderizable : _renderNodes)
					{
						rNodes += renderizable->draw(window,states);
					}
					states.transform = t;
					return rNodes;
				}

				return 0;
			}

			sptr<RenderGroup> RenderGroup::createNewRenderGroup(const std::string & name)
			{
				sptr<RenderGroup> rg = std::make_shared<RenderGroup>(name, this);
				_renderNodes.push_back(rg);
				return rg;
			}

			void RenderGroup::addRenderGroup(sptr<RenderGroup> node)
			{
				_renderNodes.push_back(node);
				__ASSERT(!node->_parent, "Node "<< node->name() <<"already has a parent");
				node->_parent = this;
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
}
