#include "textgroup.hpp"

#include <lib/scene/ianimation.hpp>
#include <lib/scene/nodes/nodeshape.hpp>
#include <lib/scene/nodes/nodetext.hpp>
#include <lib/scene/nodes/discretetext.hpp>

namespace lib
{
	namespace gui
	{
		using namespace scene;
		using namespace scene::nodes;

		TextGroup::TextGroup(SceneNode* parent, str name)
			: SceneNode{parent,std::move(name)} {}

		void TextGroup::create()
		{
		}

		void TextGroup::configure()
		{
			font.setCallback([this]() {
				for_each_text([this](const sptr<NodeText>&node) {
					node->font = font();
				});
			});

			characterSize.setCallback([this]() {
				for_each_text([this](const sptr<NodeText>&node) {
					node->characterSize = characterSize();
				});
			});

			color.setCallback([this]() {
				for_each_text([this](const sptr<NodeText>&node) {
					node->color = color();
				});
			});
		}

		sptr<NodeText> TextGroup::addTextLine(str text)
		{
			const auto bbox(boxForNextLine());
			const auto ptext = createRenderizable<NodeText>(text);
			ptext->text = std::move(text);
			ptext->font = font;
			ptext->characterSize = characterSize;
			ptext->color = color;
			ptext->alignmentBox = alignmentBox();
			ptext->alignmentX = NodeText::AlignmentX::Left;
			ptext->alignmentY = NodeText::AlignmentY::Top;
			ptext->configure();
			return ptext;
		}

		void TextGroup::for_each_text(std::function<void(const sptr<NodeText>&)> action) const
		{
			for_each_node([&action](const sptr<Renderizable>&node) {
				if (auto tnode = std::dynamic_pointer_cast<NodeText>(node)) {
					action(tnode);
				}
			});
		}

		Rectf32 TextGroup::boxForNextLine() const
		{
			const f32 delta{ static_cast<f32>(characterSize()*numLines()) };
			return alignmentBox().moveResize({0,delta}, {0,-delta});
		}
		u32 TextGroup::numLines() const
		{
			u32 count{};
			for_each_text([&count](const sptr<NodeText> &) {
				++count;
			});

			return count;
		}
	}
}
