HTPS_PRAGMA_ONCE
#ifndef HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable_data.hpp>

namespace haf::render
{
class Renderizables;
}  // namespace haf::render

namespace haf::render
{
/**
 * @brief Class to expose the data that can be modified and set by the
 * @b RenderizableBuilder
 */
struct RenderizableBuilderData
{
    htps::rptr<Renderizables> renderizables_;
    RenderizableData builder_data_;

    RenderizableData&& extract() noexcept { return htps::move(builder_data_); }
};

}  // namespace haf::render

#endif
