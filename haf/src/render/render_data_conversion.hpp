#ifndef HAF_RENDER_RENDER_DATA_CONVERSION_INCLUDE_HPP
#define HAF_RENDER_RENDER_DATA_CONVERSION_INCLUDE_HPP

#include <backend_dev/include/irenderdata.hpp>
#include "render_data.hpp"

namespace haf::render
{
backend::IRenderData to_backend(RenderData const& render_data);

}  // namespace haf::render

#endif
