#pragma once

#ifndef ZOPER_MENUSCENE_INCLUDE_HPP
#define ZOPER_MENUSCENE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/renderizables/renderizable.hpp>
#include <lib/scene/scene.hpp>
#include <lib/include/scene/iscene.hpp>

namespace zoper
{
	using namespace lib;
	class MenuScene final : public scene::Scene
	{
	public:
        using BaseClass = scene::Scene;

		DECLARE_SCENE(MenuScene)

		virtual void onCreated() override;

	private:
		ireceiver m_receiver;
	};
}

#endif