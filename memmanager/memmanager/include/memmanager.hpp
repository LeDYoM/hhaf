#ifndef HAF_MEMMANAGER_INCLUDE_HPP
#define HAF_MEMMANAGER_INCLUDE_HPP

#include <cstddef>

void installMemManager();
void finishMemManager();

void* mmalloc(std::size_t size);
void mfree(void* block);

#endif
