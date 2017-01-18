#ifndef __LIB_IDRAWABLE_HPP__
#define __LIB_IDRAWABLE_HPP__

#include <lib/include/types.hpp>
#include "hasname.hpp"

namespace lib
{
	namespace draw
	{
		class SceneNode : public core::HasName
		{
		public:
			SceneNode(const std::string &name) : core::HasName{ name } {}
			virtual ~SceneNode() = default;

			virtual void draw() = 0;

			inline bool isVisible() const noexcept { return m_visible; }
			inline void setVisible(bool nv) noexcept { m_visible = nv; }
		protected:
			bool m_visible{ true };
		};
	}
}

#endif
