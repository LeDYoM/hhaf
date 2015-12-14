#include "rendergroup.hpp"
#include "renderizable.hpp"
#include "../../core/window.hpp"

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			RenderGroup::RenderGroup(RenderGroup *parent)
				: _parent{ parent }
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

			bool RenderGroup::removeRenderizable(sptr<Renderizable> element)
			{
				auto i = _renderNodes.begin();
				bool found = false;

				while (i != _renderNodes.end() && !found)
				{
					if ((*i).get() == element.get())
					{
						i = _renderNodes.erase(i);
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

			u32 RenderGroup::drawAll(lib::core::Window *window)
			{
				u32 rNodes{ 0 };

//				auto window = p_scnManager->parentWindow();

				for (const auto renderizable : _renderNodes)
				{
					if (renderizable->isVisible())
					{
						window->draw(*(renderizable->getAsDrawable()));
						++rNodes;
					}
				}
				return rNodes;
			}

		}
	}
}
