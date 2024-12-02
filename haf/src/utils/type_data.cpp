#include <haf/include/utils/type_data.hpp>
#include <typeinfo>

using namespace htps;

namespace haf::utils
{
type_index::type_index(std::type_info const& t_info) noexcept : t_info_{&t_info}
{}

size_type type_index::hash_code() const noexcept
{
    return static_cast<htps::size_type>(t_info_->hash_code());
}

char const* type_index::name() const noexcept
{
    return t_info_->name();
}

bool type_index::operator==(type_index const& rhs) const noexcept
{
    return *t_info_ == *rhs.t_info_;
}

std::strong_ordering type_index::operator<=>(
    const type_index& rhs) const noexcept
{
    return *t_info_ == *rhs.t_info_
        ? std::strong_ordering::equal
        : t_info_->before(*rhs.t_info_) ? std::strong_ordering::less
                                        : std::strong_ordering::greater;
}

}  // namespace haf::utils
