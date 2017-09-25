#pragma once

#ifndef ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__
#define ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__

#include <lib/scene/icomponent.hpp>
#include <lib/scene/components/textselectorcontroller.hpp>
#include <lib/scene/ttfont.hpp>

namespace zoper
{
	class HighScoreTextController : public lib::scene::TextSelectorController
	{
	public:
		using ParentClassType = lib::scene::TextSelectorController;
		HighScoreTextController();
		virtual ~HighScoreTextController();

		virtual void onAttached() override;

	private:
		lib::sptr<lib::scene::TTFont> m_font;
		lib::u32 m_characterSize;
	};
}

#endif