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

			u32 RenderGroup::draw(lib::core::Window *window) const
			{
				if (isVisible())
				{
					u32 rNodes{ 0 };

					for (const auto renderizable : _renderNodes)
					{
						rNodes += renderizable->draw(window);
					}
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
