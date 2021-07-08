#ifndef HAF_BACKEND_IFACTORY_INCLUDE_HPP
#define HAF_BACKEND_IFACTORY_INCLUDE_HPP

namespace haf::backend
{
template <typename T>
class IFactoryOf
{
public:
    using Interface = T;

    virtual T* create() const      = 0;
    virtual bool destroy(T*) const = 0;
    virtual ~IFactoryOf() {}
};
}  // namespace haf::backend

#endif
