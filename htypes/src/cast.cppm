export module htypes:cast;

namespace htps
{
template <typename T, typename Y>
T d_cast(Y* element)
{
    return dynamic_cast<T>(element);
}

}  // namespace htps
