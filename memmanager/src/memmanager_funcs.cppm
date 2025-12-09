module;

#include <cstddef>

export module memmanager:funcs;

import :configuration;

namespace memm
{
export void installMemManager(int const argc, char const* argv[]);
export void installMemManager(Configuration const& configuration);
export void finishMemManager(bool const display_log);
export void* mmalloc(std::size_t const size);
export void mfree(void* block);
export void mfree_with_size(void* block, std::size_t const size);
}  // namespace memm
