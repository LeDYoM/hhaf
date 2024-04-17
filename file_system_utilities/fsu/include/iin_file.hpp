FSU_PRAGMA_ONCE
#ifndef FSU_FILE_SYSTEM_I_IN_FILE_INCLUDE_HPP
#define FSU_FILE_SYSTEM_I_IN_FILE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

namespace fsu
{
class IInFile
{
public:
    virtual bool readLine(htps::str& line) = 0;
    virtual bool eof() const = 0;
    virtual bool isOk() const = 0;

    virtual ~IInFile() = default;
};
}  // namespace fsu

#endif
