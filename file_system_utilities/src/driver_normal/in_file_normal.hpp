FSU_PRAGMA_ONCE
#ifndef FSU_FILE_SYSTEM_IN_FILE_NORMAL_INCLUDE_HPP
#define FSU_FILE_SYSTEM_IN_FILE_NORMAL_INCLUDE_HPP

#include <fsu/include/iin_file.hpp>
#include <fstream>

namespace fsu
{
class InFileNormal : public IInFile
{
public:
    explicit InFileNormal(std::ifstream file);

    htps::str readLine() override;
    bool readLine(htps::str& line) override;

    bool isOk() const override;
private:
    std::ifstream m_file;
};
}  // namespace fsu

#endif
