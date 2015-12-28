#ifndef __LIB_RENDERGROUP_HPP__
#define __LIB_RENDERGROUP_HPP__

#include "../../types.hpp"
#include "../../core/HasName.hpp"
#include "idrawable.hpp"
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

namespace lib
{
	namespace core
	{
		class Window;
	}
	namespace scn
	{
		namespace draw
		{
			class Renderizable;
			class RenderGroup : public lib::core::HasName, public IDrawable, public sf::Transformable
			{
			public:
				RenderGroup(const std::string &name, RenderGroup *parent=nullptr);
				virtual ~RenderGroup();

				sptr<draw::Renderizable> createText(const std::string &name);
				sptr<draw::Renderizable> createSprite(const std::string &name);
				sptr<draw::Renderizable> createShape(const std::string &name);
				sptr<draw::Renderizable> createCircleShape(const std::string &name);
				sptr<draw::Renderizable> addRenderizable(sptr<Renderizable> newElement);
				bool removeRenderizable(sptr<Renderizable> element);
				void clear();

				u32 draw(lib::core::Window *window, sf::RenderStates &states) const override;

				sptr<RenderGroup> createNewRenderGroup(const std::string &name);
				bool removeRenderGroup(sptr<RenderGroup> element);
			protected:
				void addRenderGroup(sptr<RenderGroup> node);

				RenderGroup *parent() const { return _parent; }

			private:
				RenderGroup *_parent{ nullptr };
				std::vector<sptr<IDrawable>> _renderNodes;
			};
		}
	}
}

#endif