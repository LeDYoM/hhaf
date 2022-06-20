#ifndef HAF_BACKEND_IFACTORY_INCLUDE_HPP
#define HAF_BACKEND_IFACTORY_INCLUDE_HPP

namespace haf::backend
{
template <typename T>
class IFactoryOf
{
public:
    using Interface = T;
    virtual ~IFactoryOf() = default;

    virtual T* create()      = 0;
    virtual bool destroy(T*) = 0;
};
}  // namespace haf::backend

#endif
