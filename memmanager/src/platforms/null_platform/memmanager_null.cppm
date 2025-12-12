export module memmanager:platform;

bool initPlatformMemManager(Configuration const&)
{
    return true;
}

bool isNativeMemoryLeakDetectorSupported()
{
    return false;
}

#endif  // _MSC_VER
