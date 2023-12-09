FSU_PRAGMA_ONCE
#ifndef FSU_IN_FILE_INCLUDE_HPP
#define FSU_IN_FILE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/p_impl_pointer.hpp>

namespace fsu
{
class FileSystem;

class InFile
{
public:
    explicit InFile(FileSystem& file_system_parent, htps::str const& file_name);
    ~InFile();

    htps::string_vector readTextFile();
    bool readTextFile(htps::string_vector& str_data);

private:
    class InFilePrivate;
    htps::PImplPointer<InFilePrivate> m_p;
};
}  // namespace fsu

#endif
