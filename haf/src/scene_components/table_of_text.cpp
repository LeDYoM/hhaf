#include <haf/include/scene_components/table_of_text.hpp>
#include <haf/include/scene_components/text.hpp>

using namespace htps;
using namespace fmath;

namespace haf::scene
{
sptr<Text> TableOfText::text(vector2dst const& index)
{
    return nodeAt(index);
}
}  // namespace haf::scene
