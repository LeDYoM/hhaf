HTPS_PRAGMA_ONCE
#ifndef HAF_RENDERIZABLES_COMPONENT_INCLUDE_HPP
#define HAF_RENDERIZABLES_COMPONENT_INCLUDE_HPP

#include <haf/include/core/types.hpp>

#include <haf/include/haf_export.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_order.hpp>

namespace haf::scene
{
class HAF_API RenderizableGroupComponent : public component::Component
{
public:
    static constexpr auto StaticTypeName{"RenderizableGroupComponent"};
    static constexpr component::ComponentOrder::Value StaticComponentOrder{0U};

    void onAttached() override;

    void update() override;

    auto renderizablesCount() const noexcept { return m_renderizables.size(); }

    bool emptyRenderizables() const noexcept { return m_renderizables.empty(); }

    decltype(auto) operator[](core::size_type const index) const noexcept
    {
        return m_renderizables[index];
    }

    auto renderizableBuilder()
    {
        return m_renderizables.renderizableBuilder();
    }

    core::sptr<render::Renderizable> const& first() const noexcept;

    core::str staticTypeName() const noexcept override;
    component::ComponentOrder::Value componentOrder() const noexcept override;

private:
    render::Renderizables m_renderizables;
};

}  // namespace haf::scene

#endif
