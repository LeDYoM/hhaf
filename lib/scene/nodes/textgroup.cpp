#include "textgroup.hpp"

#define FOR_EACH_NODETEXT_PROPERTY(prop)	m_texts.for_each([&value](const auto&param) {	\
											param -> prop = value;	\
											});

#define SET_CALLBACK_FOREACH_PROPERTY(prop)	prop .setCallback([this]() {m_texts.for_each([this](const auto&param) { param-> prop = prop (); }); });


namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			TextGroup::TextGroup(SceneNode *parent, str name)
				: SceneNode{ parent, std::move(name) } 
			{
				SET_CALLBACK_FOREACH_PROPERTY(font);
				SET_CALLBACK_FOREACH_PROPERTY(characterSize);
				SET_CALLBACK_FOREACH_PROPERTY(color);
			}

			TextGroup::~TextGroup() = default;

			void TextGroup::addText(str nTexttext)
			{
				auto nText (createRenderizable<NodeText>(make_str(name(),m_texts.size())));
				setGroupProperties(nText);
				nText->text = nTexttext;
				m_texts.push_back(std::move(nText));
			}

			void TextGroup::setGroupProperties(const sptr<NodeText>& nText)
			{
				nText->font = font();
				nText->characterSize = characterSize();
				nText->color = color();
			}

			/*
				u32 count{};
				for (auto &node : m_texts) {
					node = createRenderizable<NodeText>(name + "node_" + str(count++));
					node->font = font;
					node->characterSize = characterSize;
//					node->alignmentBox = box;
					node->alignmentX = AlignmentX::Left;
					node->alignmentY = AlignmentY::Top;
					node->color = color;
				}

				// Second text is right aligned
				m_texts[1]->alignmentX = AlignmentX::Right;

				// Third text is bottom aligned
				m_texts[2]->alignmentY = AlignmentY::Bottom;

				// Fourth text is right and bottom aligned
				m_texts[3]->alignmentX = AlignmentX::Right;
				m_texts[3]->alignmentY = AlignmentY::Bottom;
			}
			*/
		}
	}
}