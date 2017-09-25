#pragma once

#ifndef ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__
#define ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/textgroup.hpp>
#include <lib/scene/ttfont.hpp>

namespace zoper
{
	using namespace lib;

	class HighScoreTextController : public scene::SceneNode
	{
	public:
		using ParentClassType = scene::SceneNode;
		HighScoreTextController(scene::SceneNode *parent, sptr<scene::TTFont> font, const u32 characterSize);
		virtual ~HighScoreTextController();

		virtual void create() override;

	private:
		sptr<scene::nodes::TextGroup> m_textGroup;
		sptr<scene::TTFont> m_font;
		u32 m_characterSize;
	};
}

#endif