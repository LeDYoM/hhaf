FSU_PRAGMA_ONCE
#ifndef FSU_IN_FILE_INCLUDE_HPP
#define FSU_IN_FILE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/p_impl_pointer.hpp>

namespace fsu
{
class InFile
{
public:
    InFile();
    ~InFile();
private:
    class InFilePrivate;
    htps::PImplPointer<InFilePrivate> m_p;
};
}  // namespace fsu

#endif
