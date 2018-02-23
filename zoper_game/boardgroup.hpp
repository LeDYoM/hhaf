#ifndef ZOPER_BOARDGROUP_HPP__
#define ZOPER_BOARDGROUP_HPP__

#include "gamebasetile.hpp"

using namespace lib;

namespace zoper
{
	class BoardGroup : public GameBaseTile
	{
	public:
		BoardGroup(scene::SceneNode* parent, str name);
		virtual ~BoardGroup();

	private:
		static lib::u32 m_tileCounter;
	};
}

#endif
