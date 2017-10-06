#pragma once

#ifndef ZOPER_MENU_MENUPAGE_INCLUDE_HPP__
#define ZOPER_MENU_MENUPAGE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/nodes/labeltext.hpp>

namespace zoper
{
	using namespace lib;

	class MenuPage : public scene::SceneNode
	{
	public:
		using OptionType = std::pair<str, vector<str>>;
		MenuPage(lib::scene::SceneNode *parent, str name);
		virtual ~MenuPage();

		void addModelLabel(OptionType oType);

		void create() override;

		Property<Rectf32> box;

		void goDown();
		void goUp();
		void goLeft();
		void goRight();

		inline u32 selectedItem() const noexcept { return m_selectedItem; }

	protected:
		void repositionControls();

	private:
		inline const sptr<scene::nodes::LabelText> currentLine() const { return options[m_selectedItem]; }
		inline const sptr<scene::nodes::LabelText> previouscurrentLine() const { return options[m_previouslySelectedItem]; }
		u32 m_previouslySelectedItem;
		u32 m_selectedItem;

		vector<OptionType> m_model;
		vector_shared_pointers<scene::nodes::LabelText> options;
		sptr<scene::TTFont> m_normalFont;
	};
}

#endif
