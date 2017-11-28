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
#include <lib/scene/components/discretetextcomponent.hpp>
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
		using BaseClass = nodes::TableNode<TextSceneNode>;
		MenuPage(SceneNode *parent, str name);
		virtual ~MenuPage();

		void configure(MenuPageMode pageMode, const string_vector &titles, const vector<string_vector> options = {});
		void create() override;

		size_type SelectedOptionAtRow(const size_type row) const;
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

		bool nodeHasOptions(const size_type y) const noexcept;
		sptr<DiscreteTextComponent> optionsLabelAt(const size_type y);
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
