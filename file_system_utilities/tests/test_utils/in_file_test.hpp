#ifndef IINFILE_TEST_INCLUDE_HPP
#define IINFILE_TEST_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <fsu/include/iin_file.hpp>

namespace fsu_test
{
class InFileTest : public fsu::IInFile
{
public:
    explicit InFileTest(htps::str file_name) :
        m_file_name{htps::move(file_name)}
    {
        if (m_file_name == "test1.txt")
        {
            m_max_lines = 3U;
        }
    }

    bool readLine(htps::str& line) override
    {
        if (m_file_name == "test1.txt")
        {
            line = "abc";
            ++m_lines_read;
            return !eof();
        }
        return false;
    }

    bool eof() const override
    {
        return m_lines_read >= m_max_lines;
    }

    bool isOk() const override { return true; }

private:
    htps::str m_file_name;
    htps::u32 m_lines_read{0U};
    htps::u32 m_max_lines{0U};
};
}  // namespace fsu_test

#endif
