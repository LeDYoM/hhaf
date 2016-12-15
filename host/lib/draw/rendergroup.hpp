#ifndef __LIB_RENDERGROUP_HPP__
#define __LIB_RENDERGROUP_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "hasname.hpp"
#include "idrawable.hpp"
#include "animationmanager.hpp"
#include "transformable.hpp"
#include "nodeshape.hpp"
#include "nodequad.hpp"
#include "nodetext.hpp"
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
		class RenderGroup : public lib::core::HasName, public IDrawable, public anim::AnimationManager, public Transformable
		{
		public:
			RenderGroup(const std::string &name, RenderGroup *parent=nullptr);
			virtual ~RenderGroup();

			virtual void onAddedToScene() {}
			sptr<NodeText> createText(const std::string &name, const std::string& string, sptr<Font> font, u32 characterSize, const Color &color)
			{
				return createRenderizable<NodeText>(name, string, font, characterSize, color);
			}
			sptr<NodeShape> createShape(const std::string &name, const vector2df &size, sptr<Texture> texture, u32 pointCount, const Color &color)
			{
				return createRenderizable<NodeShape>(name, size, texture, pointCount, color);
			}
			sptr<NodeQuad> createSpriteShape(const std::string &name, const vector2df &size, sptr<Texture> texture, const Color &color)
			{
				return createRenderizable<NodeQuad>(name, size, texture, color);
			}

			template <typename T>
			sptr<T> addRenderizable(sptr<T> newElement)
			{
				m_renderNodes.push_back(newElement);
				return newElement;
			}

			template <typename T, typename... Args>
			sptr<T> createRenderizable(const std::string &name, Args&&... args)
			{
				auto result(msptr<T>(name, std::forward<Args>(args)...));
				m_renderNodes.emplace_back(result);
				return result;
			}

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
