#ifndef __LIB_RENDERGROUP_HPP__
#define __LIB_RENDERGROUP_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "hasname.hpp"
#include "idrawable.hpp"
#include "animationmanager.hpp"
#include "transformable.hpp"
#include <lib/core/vecsptr.hpp>

namespace lib
{
	namespace core
	{
		class Window;
	}
	namespace draw
	{
		class Scene;
		class Renderizable;
		class NodeShape;
		class NodeQuad;
		class NodeText;
		class RenderGroup : public lib::core::HasName, public IDrawable, public anim::AnimationManager, public Transformable
		{
		public:
			RenderGroup(const std::string &name, RenderGroup *parent=nullptr);
			virtual ~RenderGroup();

			virtual void onAddedToScene() {}
			sptr<NodeText> createText(const std::string &name, const std::string& string, sptr<Font> font, u32 characterSize, const Color &color);
			sptr<NodeShape> createShape(const std::string &name, const vector2df &size, sptr<Texture> texture, u32 pointCount=30, const Color &color=colors::White);
			sptr<NodeQuad> createSpriteShape(const std::string &name, const vector2df &size , sptr<Texture> texture, const Color &color = colors::White);
			sptr<draw::Renderizable> addRenderizable(sptr<Renderizable> newElement);
			bool removeRenderizable(sptr<Renderizable> element);
			void clear();

			sptr<RenderGroup> createNewRenderGroup(const std::string &name,sptr<IDrawable> beforeNode=nullptr);
			bool removeRenderGroup(sptr<RenderGroup> element);

			void draw() override;

		protected:
			void addRenderGroup(sptr<RenderGroup> node, sptr<IDrawable> beforeNode = nullptr);

			inline RenderGroup *parent() const noexcept { return m_parent; }

			template <typename T>
			inline bool isParentOfType() const noexcept
			{
				return m_parent ? dynamic_cast<T*>(m_parent) != nullptr : false;
			}

			template <typename T>
			inline T* parentAs() const noexcept
			{
				return m_parent ? dynamic_cast<T*>(m_parent) : nullptr;
			}
			virtual Scene *const parentScene() { return m_parent->parentScene(); }
			VecSPtr<IDrawable> m_renderNodes;

		private:
			RenderGroup *m_parent{ nullptr };
		};
	}
}

#endif
