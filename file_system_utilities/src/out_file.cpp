#include <fsu/include/out_file.hpp>
#include "out_file_private.hpp"

using namespace htps;

namespace fsu
{
OutFile::OutFile() : m_p{make_pimplp<OutFilePrivate>()}
{}

OutFile::~OutFile() = default;
}  // namespace fsu
