#include "rendergroup.hpp"
#include "renderizable.hpp"
#include "../../core/window.hpp"

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
			}

			sptr<draw::Renderizable> RenderGroup::createText(const std::string &name)
			{
				auto result = sptr<draw::Renderizable>(new Renderizable(name, new sf::Text));
				addRenderizable(result);
				return result;
			}

			sptr<draw::Renderizable> RenderGroup::createSprite(const std::string &name)
			{
				auto result = sptr<draw::Renderizable>(new Renderizable(name, new sf::Sprite));
				addRenderizable(result);
				return result;
			}

			sptr<draw::Renderizable> RenderGroup::createShape(const std::string &name)
			{
				auto result = sptr<draw::Renderizable>(new Renderizable(name, new sf::CircleShape));
				addRenderizable(result);
				return result;
			}

			sptr<draw::Renderizable> RenderGroup::addRenderizable(sptr<Renderizable> newElement)
			{
				_renderNodes.push_back(newElement);
				return newElement;
			}

			template <typename T>
			bool removeFromspVector(sptr<T> element,std::vector<sptr<T>> &container)
			{
				auto i = container.begin();
				bool found = false;

				while (i != container.end() && !found)
				{
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

				LOG_DEBUG("Element was" << (found ? "" : " not ") << " found. Number of left references: " << element.use_count());
				return found;
			}
			bool RenderGroup::removeRenderizable(sptr<Renderizable> element)
			{
				return removeFromspVector(element, _renderNodes);
			}

			u32 RenderGroup::draw(lib::core::Window *window) const
			{
				u32 rNodes{ 0 };

				for (const auto renderizable : _renderNodes)
				{
					rNodes += renderizable->draw(window);
				}

				for (const auto group : _childrenGroup)
				{
					rNodes += group->draw(window);
				}
				return rNodes;
			}

			sptr<RenderGroup> RenderGroup::createNewRenderGroup(const std::string & name)
			{
				auto rg = std::make_shared<RenderGroup>(name, this);
				_childrenGroup.push_back(rg);
				return rg;
			}

			bool RenderGroup::removeRenderGroup(sptr<RenderGroup> element)
			{
				return removeFromspVector(element, _childrenGroup);
			}

		}
	}
}
