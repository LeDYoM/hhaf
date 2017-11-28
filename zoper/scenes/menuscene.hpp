#pragma once

#ifndef ZOPER_MENUSCENE_INCLUDE_HPP__
#define ZOPER_MENUSCENE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/scene.hpp>

#include "../gamedata.hpp"
#include "../loaders/mainmenuresources.hpp"

namespace zoper
{
	using namespace lib;
	class MenuScene final : public scene::Scene
	{
	public:
		MenuScene();
		virtual ~MenuScene() = default;

		constexpr static f32 MenuPosX = 165.0f;

		virtual void create() override;

	private:
		ireceiver m_receiver;
		sptr<MainMenuResources> mainMenuResources;
		sptr<scene::nodes::NodeQuad> m_logo;
		sptr<scene::nodes::NodeQuad> m_background;
	};
}

#endif