#include <fsu/include/in_file.hpp>
#include "in_file_private.hpp"

using namespace htps;

namespace fsu
{
InFile::InFile() : m_p{make_pimplp<InFilePrivate>()}
{}

InFile::~InFile() = default;
}  // namespace fsu
