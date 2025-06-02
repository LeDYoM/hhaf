#ifndef MEMMANAGER_MSC_HPP
#define MEMMANAGER_MSC_HPP

#ifdef _MSC_VER
#ifndef NDEBUG
int crtDebugMemAllocHook(int allocType,
                                void* userData,
                                size_t size,
                                int blockType,
                                long requestIndex,
                                const unsigned char* fileName,
                                int lineIndex) noexcept;
#endif  // NDEBUG
#endif  // _MSC_VER

bool initPlatformMemManager();

#endif
