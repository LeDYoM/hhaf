export module host:host_private;

namespace haf::host
{
struct Host::HostPrivate : public HostInternal
{
    using HostInternal::HostInternal;
};

}  // namespace haf::host
