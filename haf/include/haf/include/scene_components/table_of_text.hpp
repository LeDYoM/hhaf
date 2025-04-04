HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENTS_TABLE_OF_TEXT_INCLUDE_HPP
#define HAF_COMPONENTS_TABLE_OF_TEXT_INCLUDE_HPP

#include <facil_math/include/vector_types.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/scene_components/table_of.hpp>
#include <haf/include/scene_components/text.hpp>

namespace haf::scene
{
class TableOfText : public TableOf<Text>
{
    using BaseClass = TableOf<Text>;

public:
    using BaseClass::BaseClass;

    htps::sptr<Text> text(fmath::vector2dst const& index);
};
}  // namespace haf::scene

#endif
