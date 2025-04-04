HTPS_PRAGMA_ONCE
#ifndef HAF_TABLE_OF_TEXT_QUAD_INCLUDE_HPP
#define HAF_TABLE_OF_TEXT_QUAD_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/scene_components/table_of_text.hpp>
#include <haf/include/scene_components/text.hpp>

namespace haf::scene
{
class TableOfTextQuad : public TableOfText
{
    using Base = TableOfText;

public:
    using Base::Base;

    void onAttached() override;

    void onElementCreated(fmath::vector2dst, htps::sptr<Text> const&);
};
}  // namespace haf::scene

#endif
