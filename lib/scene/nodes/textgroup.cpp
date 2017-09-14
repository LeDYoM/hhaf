#include "textgroup.hpp"

#define FOR_EACH_NODETEXT_PROPERTY(prop)	m_texts.for_each([&value](const auto&param) {	\
											param -> prop = value;	\
											});

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			TextGroup::TextGroup(SceneNode *parent, str name)
				: SceneNode{ parent, std::move(name) } {}

			TextGroup::~TextGroup() = default;

			void TextGroup::create()
			{
			}

			void TextGroup::setFont(sptr<scene::TTFont> value) noexcept
			{
				FOR_EACH_NODETEXT_PROPERTY(font);
			}

			void TextGroup::setColor(const Color &value) noexcept
			{
				FOR_EACH_NODETEXT_PROPERTY(color);
			}

			void TextGroup::setCharacterSize(const u32 value) noexcept
			{
				FOR_EACH_NODETEXT_PROPERTY(characterSize);
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