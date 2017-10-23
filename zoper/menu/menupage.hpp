#pragma once

#ifndef ZOPER_MENU_MENUPAGE_INCLUDE_HPP__
#define ZOPER_MENU_MENUPAGE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/scenenodetypes.hpp>
#include <lib/scene/color.hpp>

namespace zoper
{
	using namespace lib;

	class MenuPage : public scene::nodes::TableNode<scene::TextSceneNode>
	{
	public:
		using BaseClass = scene::nodes::TableNode<scene::TextSceneNode>;
		MenuPage(scene::SceneNode *parent, str name);
		virtual ~MenuPage();

		void setMainLabels(const vector<str>& texts, const Rectf32 &textBox);

		void create() override;

		Property<Rectf32> box;

		void goDown();
		void goUp();
		void goLeft();
		void goRight();

		inline u32 selectedItem() const noexcept { return m_selectedItem; }

	protected:
		void update();

	private:
		void updateSelection();
		void setColorToLine(const size_type, const scene::Color&);
		size_type m_previouslySelectedItem{ 0 };
		size_type m_selectedItem{ 0 };

		sptr<scene::TTFont> m_normalFont;
		ireceiver m_receiver;
	};
}

#endif
