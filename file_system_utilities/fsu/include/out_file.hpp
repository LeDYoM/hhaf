FSU_PRAGMA_ONCE
#ifndef FSU_OUT_FILE_INCLUDE_HPP
#define FSU_OUT_FILE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/p_impl_pointer.hpp>

namespace fsu
{
class OutFile
{
public:
    OutFile();
    ~OutFile();
private:
    class OutFilePrivate;
    htps::PImplPointer<OutFilePrivate> m_p;
};
}  // namespace fsu

#endif
