HTPS_PRAGMA_ONCE
#ifndef HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP

#include <haf/include/core/types.hpp>
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
class RenderizableBuilderData
{
public:
    constexpr explicit RenderizableBuilderData(
        core::rptr<Renderizables> renderizables) noexcept :
        m_renderizables{renderizables}, m_builder_data{}
    {}

    RenderizableData&& extract() && noexcept
    {
        return htps::move(m_builder_data);
    }

    constexpr core::rptr<Renderizables> renderizables() noexcept
    {
        return m_renderizables;
    }

    constexpr core::rptr<Renderizables> renderizables() const noexcept
    {
        return m_renderizables;
    }

    constexpr RenderizableData& renderizableData() noexcept
    {
        return m_builder_data;
    }

    constexpr RenderizableData const& renderizableData() const noexcept
    {
        return m_builder_data;
    }

private:
    core::rptr<Renderizables> m_renderizables;
    RenderizableData m_builder_data;
};

}  // namespace haf::render

#endif
