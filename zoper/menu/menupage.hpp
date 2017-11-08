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
#include "menupagetype.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	enum class MenuPageMode {
		Selector,
		Optioner
	};

	class MenuPage : public nodes::TableNode<TextSceneNode>
	{
	public:
		using BaseClass = scene::nodes::TableNode<scene::TextSceneNode>;
		MenuPage(SceneNode *parent, str name);
		virtual ~MenuPage();

		void configure(MenuPageMode pageMode, const Rectf32 &textBox, const string_vector &titles, const vector<string_vector> options = {});
		void create() override;

		emitter<const MenuPageType> Forward;
		emitter<> Back;

	protected:
		emitter<const size_type> Selection;
	private:
		void standarizeText(sptr<nodes::NodeText> ntext);
		void goDown();
		void goUp();
		void goLeft();
		void goRight();
		void goSelected();

		void setSelectedItem(const size_type index);
		void updateSelection();
		void setColorToLine(const size_type, const scene::Color&);
		size_type m_previouslySelectedItem{ 0 };
		size_type m_selectedItem{ 0 };

		sptr<TTFont> m_normalFont;
		Color m_normalColor;
		Color m_selectedColor;
		size_type m_normalCharacterSize;
		ireceiver m_receiver;
		MenuPageMode m_pageMode;
	};
}

#endif
