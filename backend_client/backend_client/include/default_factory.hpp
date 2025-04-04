#ifndef HAF_BACKEND_DEFAULT_FACTORY_INCLUDE_HPP
#define HAF_BACKEND_DEFAULT_FACTORY_INCLUDE_HPP

#include <backend_dev/include/ifactory.hpp>

namespace haf::backend::client
{
template <typename T, typename ConcreteObject>
class DefaultFactoryOf : public IFactoryOf<T>
{
public:
    using Interface              = typename IFactoryOf<T>::Interface;
    ~DefaultFactoryOf() override = default;

    T* create() override { return new ConcreteObject; }

    bool destroy(T* obj) override
    {
        delete obj;
        return true;
    }
};
}  // namespace haf::backend::client

#endif
