#pragma once

#ifndef ZOPER_MENU_MENUPAGE_INCLUDE_HPP__
#define ZOPER_MENU_MENUPAGE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/scenenodetypes.hpp>

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
		inline vector_shared_pointers<scene::TextSceneNode> currentLine() const { return getX(m_selectedItem); }
		inline vector_shared_pointers<scene::TextSceneNode> previouscurrentLine() const { return getX(m_previouslySelectedItem); }
		bool previouslySelectedExists{ false };
		size_t m_previouslySelectedItem{ 0 };
		size_t m_selectedItem{ 0 };

		sptr<scene::TTFont> m_normalFont;
		ireceiver m_receiver;
	};
}

#endif
