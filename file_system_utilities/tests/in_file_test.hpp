#ifndef IINFILE_TEST_INCLUDE_HPP
#define IINFILE_TEST_INCLUDE_HPP

#include <fsu/include/iin_file.hpp>

namespace fsu_test
{
class InFileTest : public fsu::IInFile
{
public:
    explicit InFileTest(std::ifstream file);

    htps::str readLine() override;
    bool readLine(htps::str& line) override;

    bool isOk() const override;
};
}  // namespace fsu

#endif
