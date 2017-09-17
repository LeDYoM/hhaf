#pragma once

#ifndef LIB_CONTROLLER_TEXTSELECTORCONTROLLER_HPP__
#define LIB_CONTROLLER_TEXTSELECTORCONTROLLER_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <lib/scene/icomponent.hpp>

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			class TextGroup;
			class NodeText;
		}
		class TextSelectorController : public IComponent
		{
		public:
			TextSelectorController();
			~TextSelectorController();

			void onAttached() override;
			void update() override;
			void addText(str text);

			void selectNext(const bool goBack);
			void selectPrevious(const bool goLast);
			void selectIndex(const s32 index);
		private:
			sptr<nodes::TextGroup> m_textGroup;
			sptr<nodes::NodeText> m_selectedText;
			s32 m_selected{ -1 };
		};
	}
}

#endif
