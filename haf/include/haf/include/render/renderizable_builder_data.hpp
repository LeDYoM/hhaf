#ifndef HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/render/renderizable_data.hpp>

namespace haf::render
{
struct RenderizableModifierContext;
class Renderizables;
}  // namespace haf::render

namespace haf::render
{
struct RenderizableBuilderData
{
    htps::rptr<Renderizables> renderizables_;
    RenderizableData builder_data_;
    function<scene::Color(const RenderizableModifierContext&)> color_modifier_;

    RenderizableData&& extract() noexcept { return std::move(builder_data_); }
};

}  // namespace haf::render

#endif
