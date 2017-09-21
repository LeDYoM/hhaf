#pragma once

#ifndef ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__
#define ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__

#include <lib/scene/icomponent.hpp>
#include <lib/scene/components/textselectorcontroller.hpp>

namespace zoper
{
	class HighScoreTextController : public lib::scene::TextSelectorController
	{
	public:
		using ParentClassType = lib::scene::TextSelectorController;
		HighScoreTextController();
		virtual ~HighScoreTextController();

		virtual void onAttached() override;

	};
}

#endif