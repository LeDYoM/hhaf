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
			class NodeShape;
			class NodeText;
			class RenderGroup : public lib::core::HasName, public IDrawable, public anim::AnimationManager, public sf::Transformable
			{
			public:
				RenderGroup(const std::string &name, RenderGroup *parent=nullptr);
				virtual ~RenderGroup();

				sptr<NodeText> createText(const std::string &name);
				sptr<NodeShape> createShape(const std::string &name,const sf::Vector2f &radius=sf::Vector2f(),u32 pointCount=30);
				sptr<NodeShape> createSpriteShape(const std::string &name, const sf::Vector2f &radius = sf::Vector2f());
				sptr<draw::Renderizable> addRenderizable(sptr<Renderizable> newElement);
				bool removeRenderizable(sptr<Renderizable> element);

				template <typename T> sptr<T> createSceneNode(const std::string &name)
				{
					auto result = std::make_shared<T>(name);
					addNode(result);
					return result;
				}

				bool addNode(sptr<ISceneNode> node);
				bool removeNode(sptr<ISceneNode> node);

				void clear();

				template <typename T>
				sptr<T> createNode(const std::string &name)
				{

				}

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
