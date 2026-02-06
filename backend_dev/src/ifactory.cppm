export module backend_dev:ifactory;

namespace haf::backend
{
export template <typename T>
class IFactoryOf
{
public:
    using Interface       = T;
    virtual ~IFactoryOf() = default;

    virtual T* create()      = 0;
    virtual bool destroy(T*) = 0;
};
}  // namespace haf::backend
