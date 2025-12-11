module;

#include <cstddef>

export module memmanager:funcs;

import :configuration;

namespace memm
{
export bool initMemManager(Configuration const& configuration);
export bool initMemManager();
export bool initMemManager(int const argc, char const* argv[]);
export bool finishMemManager(bool const display_log);
export void* mmalloc(std::size_t const size);
export void mfree(void* block);
export void mfree_with_size(void* block, std::size_t const size);
export bool isInitialized() noexcept;
export bool isNativeMemoryLeakDetectorSupported() noexcept;

/**
 * @return bool If the memory leak detector has been initialized and it is
 * active.
 */
export bool isMemoryLeakDetectorActive() noexcept;

}  // namespace memm
