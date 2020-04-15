#ifndef HAF_MEMMANAGER_INCLUDE_HPP
#define HAF_MEMMANAGER_INCLUDE_HPP

void installMemManager();
void finishMemManager();

void* mmalloc(unsigned long long size);
void mfree(void* block);

#endif
