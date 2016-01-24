#ifndef __LIB_RENDERGROUP_HPP__
#define __LIB_RENDERGROUP_HPP__

#include "../../types.hpp"
#include "../../core/HasName.hpp"
#include "idrawable.hpp"
#include "anim/animationmanager.hpp"
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
			class RenderGroup : public lib::core::HasName, public IDrawable, public anim::AnimationManager, public sf::Transformable
			{
			public:
				RenderGroup(const std::string &name, RenderGroup *parent=nullptr);
				virtual ~RenderGroup();

				sptr<draw::Renderizable> createText(const std::string &name);
				sptr<draw::Renderizable> createShape(const std::string &name,const sf::Vector2f &radius=sf::Vector2f(),u32 pointCount=30);
				sptr<draw::Renderizable> createSpriteShape(const std::string &name, const sf::Vector2f &radius = sf::Vector2f());
				sptr<draw::Renderizable> addRenderizable(sptr<Renderizable> newElement);
				bool removeRenderizable(sptr<Renderizable> element);
				void clear();

				sptr<RenderGroup> createNewRenderGroup(const std::string &name,sptr<IDrawable> beforeNode=nullptr);
				bool removeRenderGroup(sptr<RenderGroup> element);

				virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const override;

			protected:
				void addRenderGroup(sptr<RenderGroup> node, sptr<IDrawable> beforeNode = nullptr);

				RenderGroup *parent() const { return _parent; }
				std::vector<sptr<IDrawable>> _renderNodes;

			private:
				RenderGroup *_parent{ nullptr };
			};
		}
	}
}

#endif
