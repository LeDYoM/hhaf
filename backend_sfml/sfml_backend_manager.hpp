#include <backend_client/include/default_backend_manager.hpp>

class SFMLBackendManager : public haf::backend::client::DefaultBackendManager
{
public:
    void create() override;
};
