export module memmanager:configuration;

export struct Configuration
{
    bool AlwaysCheckHeap{false};  // Check heap every alloc/dealloc
};
